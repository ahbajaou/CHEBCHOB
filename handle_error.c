/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:16:10 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/28 09:44:04 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct t_global_status	g_exit;

void	error(t_errortype type, t_cmd *cmd)
{
	if (type == ERROR_DOC)
	{
		g_exit._exit = 126;
		write(2, "No such file or directory\n", 26);
		return ;
	}
	if (type == ERROR_SYNTAX)
		write(2, "syntax error\n", 13);
	else if (type == ERROR_PIPE)
	{
		g_exit._exit = 2;
		write(2, "syntax error near unexpected token `|'.\n", 41);
	}
	else if (type == ERROR_DOUBLE_PIPE)
	{
		g_exit._exit = 2;
		write(2, "syntax error near unexpected token `||'.\n", 42);
	}
	else if (type == REDIR_ERROR)
	{
		if (!cmd)
			{
				g_exit._exit = 2;
				write(2, "syntax error near unexpected token `newline'\n", 46);
				return ;
			}
		if (!cmd || !strstr(cmd->name, "/bin/"))
			return ;
		if (!cmd || !strstr(cmd->name, "../") || strstr(cmd->name, "./"))
			return ;
		g_exit._exit = 2;
		write(2, "syntax error near unexpected token `newline'\n", 46);
	}
	else if (type == REDIR_ERROR_L1R1)
	{
		g_exit._exit = 2;
		write(2, "syntax error near unexpected token `<>'\n", 39);
	}
	else if (type == ERROR_CNF)
	{
		g_exit._exit = 127;
		write(2, "command not found\n", 18);
	}
	else
	{
		g_exit._exit = 1337;
		write(2, "Oopsie daisy! We kinda forgot this one... 😅🛸\n", 49);
	}
}
