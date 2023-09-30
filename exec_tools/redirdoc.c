/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirdoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:09:55 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 01:18:55 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir(t_cmd *cmd)
{
	int	fdd;

	if (!cmd || !cmd->redirections)
		return ;
	if (cmd->redirections->redirection_type == REDIR_INPUT)
	{
		cmd->inf = open(cmd->redirections->filename, O_RDONLY, 0644);
		dup2(cmd->inf, STDIN_FILENO);
		close(cmd->inf);
	}
	if (cmd->redirections->redirection_type == REDIR_OUTPUT)
	{
		cmd->outf = open(cmd->redirections->filename, O_CREAT | O_RDWR, 0644);
		dup2(cmd->outf, STDOUT_FILENO);
		close(cmd->outf);
	}
	if (cmd->redirections->redirection_type == REDIR_APPEND)
	{
		fdd = open(cmd->redirections->filename, O_CREAT | O_RDWR
				| O_APPEND, 0644);
		dup2(fdd, STDOUT_FILENO);
		close(fdd);
	}
}

void	herdoc2(t_cmd *cmd, int fd, int open_file, char *file_name)
{
	char	*temp;
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	temp = get_next_line(fd);
	if (!temp)
		return ;
	line = ft_substr(temp, 0, strlen(temp) - 1);
	free(temp);
	open_file = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (ft_strcmp(line, cmd->redirections->filename))
	{
		write(open_file, line, strlen(line));
		write(open_file, "\n", 1);
		temp = get_next_line(fd);
		free(line);
		if (!temp)
			return ;
		line = ft_substr(temp, 0, strlen(temp) - 1);
		free(temp);
	}
	close(open_file);
	free(line);
}

void	herdoc(t_cmd *cmd)
{
	char	*file_name;
	int		fd;
	int		open_file;

	file_name = "outfile";
	fd = 0;
	open_file = 0;
	if (cmd)
		if (!cmd->redirections)
			return ;
	if (ft_strcmp(cmd->name, "cat") == 0)
		fd = 1;
	if (cmd->redirections->redirection_type == REDIR_HEREDOC)
	{
		herdoc2(cmd, fd, open_file, file_name);
		if (cmd->redirections->next)
			return ;
		open_file = open(file_name, O_RDONLY, 0644);
		dup2(open_file, STDIN_FILENO);
		close(open_file);
		unlink(file_name);
		free(cmd->redirections->filename);
		cmd->redirections->filename = NULL;
	}
}
