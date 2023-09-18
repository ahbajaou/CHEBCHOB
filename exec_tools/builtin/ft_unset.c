

#include "../../minishell.h"

void        delet_unset(ev_list **env,char *key)
{
    ev_list *tmp;
    ev_list *perv;

    perv = NULL;
    tmp = *env;

    if (env != NULL)
    {
        if (ft_strcmp(tmp->key, key) != 0)
        {
            while (tmp->next)
            {
                if (ft_strcmp(tmp->next->key, key) == 0)
                {
                    perv = tmp->next;
                    free(tmp->next->key);
                    free(tmp->next->value);
                    tmp->next = tmp->next->next;
                    free(perv);
                    return ;
                }
                tmp = tmp->next;
            }
        }
        else
        {
            tmp = (*env);
            (*env) = (*env)->next;
            free(tmp->key);
            free(tmp->value);
        }

    }
}

void    ft_unset(ev_list **env, t_cmd *cmd)
{
    int i = 0;
    while (cmd->args[i])
    {
        delet_unset(env,cmd->args[i]);
        i++;
    }
}