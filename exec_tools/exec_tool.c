/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:59:27 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 00:46:56 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd2(t_cmd *cmd, t_list **env)
{
	cmd->vex = execve_cmd(cmd, *env);
	if (!cmd->vex)
		cmd->vex = ft__strdup(cmd->name);
	cmd->execve[0] = cmd->name;
	cmd->execve[1] = cmd->args[0];
	cmd->execve[2] = NULL;
	if (checkerrer(cmd, *env) == 0)
	{
		if (cmd->vex)
		{
			free(cmd->vex);
			cmd->vex = NULL;
		}
		if (checkbuilt(cmd, env) == 1)
			return ;
		return ;
	}
}

void	pipeline(t_cmd *cmd, int fdd, int fd[2])
{
	sigchild();
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
	while (cmd->redirections)
	{
		redir(cmd);
		herdoc(cmd);
		cmd->redirections = cmd->redirections->next;
	}
}

void	executecmd(t_cmd *cmd, t_list **env, char **envp)
{
	if (check_builting(cmd, env) != 1)
	{
		if (!cmd->vex)
			return ;
		if (!execve(cmd->vex, cmd->execve, envp))
			perror("execve");
		exit(0);
	}
}

void	_waitpid(int cnt_pipe)
{
	int	j;

	j = 0;
	while (j < cnt_pipe)
	{
		wait(NULL);
		j++;
	}
}
