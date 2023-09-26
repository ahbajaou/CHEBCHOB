/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:16:10 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/25 10:26:23 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct global_status	g_exit;

void error(ErrorType type,t_cmd *cmd)
{
    if (type == ERROR_DOC)
    {
        g_exit._exit = 126;
        printf("No such file or directory\n");
        return ;
    }
    if (type == ERROR_SYNTAX)
        fprintf(stderr, "syntax error\n");
    else if (type == ERROR_PIPE) 
    {
        g_exit._exit = 2;
        fprintf(stderr, "syntax error near unexpected token `|'.\n");
    }
    else if (type == ERROR_DOUBLE_PIPE) 
    {
        g_exit._exit = 2;
        fprintf(stderr, "syntax error near unexpected token `||'.\n");
    }
    else if (type == REDIR_ERROR)
    {
        if (strstr(cmd->name,"/bin/"))
            return ;
        if (strstr(cmd->name,"../") || strstr(cmd->name,"./"))
            return ;
        g_exit._exit = 2;
        fprintf(stderr, "syntax error near unexpected token `newline'\n");

    }
    else if (type == REDIR_ERROR_L1R1)
    {
        g_exit._exit = 2;
        fprintf(stderr, "syntax error near unexpected token `<>'\n");
    }
    else if (type == ERROR_CNF)
    {
        g_exit._exit = 127;
        fprintf(stderr, "command not found\n");
    }
    else 
    {
        g_exit._exit = 1337;
        fprintf(stderr, "Oopsie daisy! We kinda forgot this one... 😅🛸\n");
    }
}
