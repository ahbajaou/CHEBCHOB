
#include "../../minishell.h"

void    update_path(ev_list *env, char *old,char *new)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp("PWD", tmp->key) == 0 && new != NULL)
        {
            free(tmp->value);
            tmp->value = ft__strdup(new);
        }
        if (ft_strcmp("OLDPWD", tmp->key) == 0 && old != NULL)
        {
            free(tmp->value);
            tmp->value = ft__strdup(old);
        }
        tmp = tmp->next;
    }
    free(tmp);
}

void _exec_cd(ev_list **env,char *name)
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_path(*env,cwd,NULL);
    if (ft_strcmp(name,"..") != 0)
            chdir(name);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_path(*env,NULL,cwd);
}
char *_getenv(ev_list **env)
{
    ev_list *tmp;
    tmp = *env;
    while (tmp)
    {
        if (ft_strcmp(tmp->key,"HOME") == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    free(tmp);
    return (NULL);
}
void    ft_cd(t_cmd *cmd, ev_list **env)
{
    if (ft_strcmp("..", cmd->args[0]) == 0)
         _exec_cd(env,cmd->args[0]);
    else if (ft_strcmp("~", cmd->args[0]) == 0 || !cmd->args[0])
    {
        char *path = _getenv(env);
        if (!path)
        {
            printf("minishell: cd: HOME not set\n");
            return ;
        }
        _exec_cd(env,path);
    }
    else
        _exec_cd(env,cmd->args[0]);
    return ;
}