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

char **get_path(ev_list *env,t_cmd *cmd)
{
    ev_list *tmp;
    (void)cmd;
    tmp = (env);

    char *path;
    path = NULL;
    char **spl;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, "PATH") == 0)
                path = ft__strdup(tmp->value);
        tmp = tmp->next;
    }
    if (!path)
    {
        // printf("No such file or directory\n");
        free(tmp);
        tmp = NULL;
        return NULL;
    }
    spl = ft_split(path, ':');
    free(path);
    free(tmp);
    tmp = NULL;
    return (spl);
}

char *access_ve(char **path,t_cmd *cmd)
{

    // t_cmd *tmp;

    // tmp = cmd;
    int i = 0;
    char *current;
    // char *p;
    if (!path)
    {
        return NULL;
    }
    // while (tmp)
    // {
        while (path[i])
        {
            current = ft_join2(path[i],"/");
            current = ft_join2(current,cmd->name);
            if (!access(current,F_OK))
            {
                free4free(path + i + 1);
                free(path);
                // free(p);
                return (current);
            }
            // if (access(current,F_OK))
            free(current);
            i++;
        }
    //     tmp = tmp->next;
    // }
    free(path);
    // free(tmp);
    // free(current);
    // tmp = NULL;
    return (NULL);
}