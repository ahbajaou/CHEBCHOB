

#include "../../minishell.h"

int       delet_unset(ev_list **env,char *key)
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
                    return (1);
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
            return (1);
        }
    }
    return (0);
}

void    ft_unset(ev_list **env, t_cmd *cmd)
{
    int i = 0;
        while (cmd->args[i])
        {
            if (delet_unset(env,cmd->args[i]) == 1)
                return ;
            
            i++;
        }

}