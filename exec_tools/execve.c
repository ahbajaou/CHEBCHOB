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

void _free(char **path)
{
    // int i = 0;
    int cnt = 0;
    while (path[cnt])
    {
        free(path[cnt]);
        cnt++;
    }
    free(path[cnt]);

}

char    *execve_cmd(t_cmd *cmd, ev_list *env)
{

    char **path = get_path(env);
    char *p = access_ve(path,cmd);
        if (!access(p,F_OK))
            return (p);
    free(p);
    return (NULL);
}
