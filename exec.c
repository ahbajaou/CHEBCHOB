/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:46:38 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 10:00:36 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct global_status	g_exit;

global_status				g_exit;
void	exec_cmd2(t_cmd *cmd, ev_list **env)
{
	cmd->vex = execve_cmd(cmd, *env);
	if (!cmd->vex)
		cmd->vex = ft__strdup(cmd->name);
	cmd->execve[0] = cmd->name;
	cmd->execve[1] = cmd->args[0];
	cmd->execve[2] = NULL;
	if (checkErrer(cmd, *env) == 0)
	{
		if (checkbuilt(cmd, env) == 1)
		{
			if (cmd->vex)
			{
				free(cmd->vex);
				cmd->vex = NULL;
			}
			return ;
		}
		return ;
	}
}

void	pipeline(t_cmd *cmd, int fdd, int fd[2])
{
	if (fdd != 0)
	{
		dup2(fdd, STDIN_FILENO);
		close(fdd);
	}
	if (cmd->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

void	_redirection(t_cmd *cmd)
{
	t_redirection_list *original_redirections = cmd->redirections;
	while (cmd->redirections)
	{
		redir(cmd);
		herdoc(cmd, NULL);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = original_redirections;
}

void	executecmd(t_cmd *cmd, ev_list **env, char **envp)
{
	if (check_builting(cmd, env) != 1)
	{
		if (!cmd->vex)
			return ;
		if (!execve(cmd->vex, cmd->execve, envp))
			perror("execve");
	}
}

void	exec_cmd(t_cmd *cmd, ev_list **env, char **envp)
{
	int	cnt_pipe;
	int	j;
	int	fdd;
	int	fd[2];

	cnt_pipe = 0;
	j = 0;
	fdd = 0;
	if (cmd->next == NULL)
		parentbuilt(cmd, env);
	while (cmd != NULL)
	{
		exec_cmd2(cmd, env);
		if (pipe(fd) == -1)
			perror("pipe");
		cmd->pid = fork();
		if (cmd->pid == -1)
			perror("fork");
		if (cmd->pid == 0)
		{
			signal(SIGQUIT, sighandler);
			pipeline(cmd, fdd, fd);
			close(fd[0]);
			_redirection(cmd);
			close(fd[0]);
			executecmd(cmd, env, envp);
			exit(1);
		}
		if (cmd->vex)
			free(cmd->vex);
		if (fdd != 0)
			close(fdd);
		fdd = fd[0];
		close(fd[1]);
		cmd = cmd->next;
		cnt_pipe++;
	}
	while (j < cnt_pipe)
	{
		wait(NULL);
		j++;
	}
}
