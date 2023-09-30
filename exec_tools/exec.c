/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:50:38 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 01:18:02 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_global_status	g_exit;

void	_close(int fdd)
{
	if (fdd != 0)
		close(fdd);
}

void	pipe_fork(t_cmd *cmd, t_list **env, int fd[2])
{
	sigcmd();
	exec_cmd2(cmd, env);
	if (pipe(fd) == -1)
		perror("pipe");
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
}

void	parentexec(t_cmd *cmd, t_list **env)
{
	if (cmd->next == NULL)
		parentbuilt(cmd, env);
}

void	free4cmd(char *cmd)
{
	if (cmd)
		free(cmd);
}

void	exec_cmd(t_cmd *cmd, t_list **env, char **envp, int cnt_pipe)
{
	int	fdd;
	int	fd[2];

	cnt_pipe = 0;
	fdd = 0;
	parentexec(cmd, env);
	while (cmd != NULL)
	{
		pipe_fork(cmd, env, fd);
		if (cmd->pid == 0)
		{
			pipeline(cmd, fdd, fd);
			close(fd[0]);
			_redirection(cmd);
			executecmd(cmd, env, envp);
			exit(0);
		}
		free4cmd(cmd->vex);
		_close(fdd);
		fdd = fd[0];
		close(fd[1]);
		cmd = cmd->next;
		cnt_pipe++;
	}
	_waitpid(cnt_pipe);
}
