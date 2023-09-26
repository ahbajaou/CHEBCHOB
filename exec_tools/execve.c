/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:36:58 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/24 20:16:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


extern struct global_status g_exit;

char    *execve_cmd(t_cmd *cmd, ev_list *env)
{

    char **path = get_path(env,cmd);
    char *p = access_ve(path,cmd);
    if (!p)
    {
        if (ft_strcmp(cmd->name,"exit") == 0)
            printf("exit\n");
        else if (ft_strcmp(cmd->name,"cd") == 0)
            return (NULL);
        else if (ft_strcmp(cmd->name,"export") == 0)
            return (NULL);
        else if (ft_strcmp(cmd->name,"unset") == 0)
            return (NULL);
        else if (((cmd->name[0] >= 'a' && cmd->name[0] <= 'z'))
            || ((cmd->name[0] >= 'A' && cmd->name[0] <= 'Z'))
                || (cmd->name[0] >= '0' && cmd->name[0] <= '9'))
                {
                    error(ERROR_CNF,cmd);
                    g_exit._exit = 127;
                    return (NULL);
                }
        else
        {
            error(REDIR_ERROR,cmd);
            g_exit._exit = 2;
            return (NULL);
        }
        return (NULL);
    }
    return (p);
}
