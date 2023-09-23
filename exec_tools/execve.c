/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:36:58 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/17 04:51:11 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char    *execve_cmd(t_cmd *cmd, ev_list *env)
{

    char **path = get_path(env,cmd);
    char *p = access_ve(path,cmd);
    if (!p)
    {
        // if ((cmd->name[0] >= 'a' && cmd->name[0] <= 'z') || (cmd->name[0] >= 'A' && cmd->name[0] <= 'Z')
        // || (cmd->name[0] >= '0' && cmd->name[0] <= '9'))
        // {
        //     printf("%s : command not found\n",cmd->name);
        //     return (p);
        // }
        // else
        //     printf("bash: syntax error\n");

    }
    return (p);
}
