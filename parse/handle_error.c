/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:16:10 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/30 01:12:18 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern struct t_global_status	g_exit;

void	handle_doc_error(void)
{
	g_exit._exit = 126;
	write(2, "No such file or directory\n", 26);
}

void	handle_pipe_errors(t_errortype type, t_cmd *cmd)
{
	if (type == ERROR_PIPE)
		write(2, "syntax error near unexpected token `|'.\n", 41);
	else if (type == ERROR_DOUBLE_PIPE)
		write(2, "syntax error near unexpected token `||'.\n", 42);
	else if (type == REDIR_ERROR)
	{
		if (!cmd || !strstr(cmd->name, "/bin/") || !strstr(cmd->name, "../")
			|| strstr(cmd->name, "./"))
			return ;
		write(2, "syntax error near unexpected token `newline'\n", 46);
	}
	else if (type == REDIR_ERROR_L1R1)
		write(2, "syntax error near unexpected token `<>'\n", 39);
	else
		write(2, "Oopsie daisy! We kinda forgot this one... 😅🛸\n", 49);
}

void	error(t_errortype type, t_cmd *cmd)
{
	if (!cmd)
	{
		g_exit._exit = 127;
		write(2, "command not found\n", 18);
		return ;
	}
	if (type == ERROR_DOC)
		handle_doc_error();
	else if (type == ERROR_SYNTAX)
		write(2, "syntax error\n", 13);
	else if (type == ERROR_PIPE || type == ERROR_DOUBLE_PIPE
		|| type == REDIR_ERROR || type == REDIR_ERROR_L1R1)
		handle_pipe_errors(type, cmd);
	else if (type == ERROR_CNF)
	{
		g_exit._exit = 127;
		write(2, "command not found\n", 18);
	}
	else
		handle_pipe_errors(type, cmd);
}
