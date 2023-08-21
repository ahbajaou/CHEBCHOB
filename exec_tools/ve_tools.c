/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ve_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:52:05 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/07/17 03:32:17 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_path(ev_list *env)
{
    ev_list *tmp;
    tmp = (env);
    char *path;
    char **spl;
    while (tmp)
    {
        if (strcmp(tmp->key, "PATH") == 0)
                path = ft__strdup(tmp->value);
        tmp = tmp->next;
    }
    free(tmp);
    spl = ft_split(path, ':');
    free(path);
    return (spl);
}

char *access_ve(char **path,t_cmd *cmd)
{

    t_cmd *tmp;

    (void)path;
    tmp = cmd;
    int i = 0;
    char *current;
    char *p;
    while (tmp)
    {
        while (path[i])
        {
            current = ft_join2(path[i],"/");
            p = ft_join2(current,cmd->name);
            if (!access(p,F_OK))
                return (p);
            i++;
        }
        // free(current);
        tmp = tmp->next;
    }
            // free(current);
    free(tmp);
    // free(path);
    // free(p);
    return (NULL);
}