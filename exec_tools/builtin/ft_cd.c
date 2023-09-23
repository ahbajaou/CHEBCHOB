
#include "../../minishell.h"

void    update_path(ev_list *env, char *old,char *new)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp("PWD", tmp->key) == 0 && new != NULL)
            tmp->value = ft__strdup(new);
        if (ft_strcmp("OLDPWD", tmp->key) == 0 && old != NULL)
            tmp->value = ft__strdup(old);
        tmp = tmp->next;
    }
    free(tmp);
}

void _exec_cd(ev_list **env,char *name)
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_path(*env,cwd,NULL);
    if (chdir(name))
        printf("cd No such file or directory\n");
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_path(*env,NULL,cwd);
}
void    ft_cd(t_cmd *cmd, ev_list **env)
{
    ev_list *tmp;

    tmp = *env;
    if (ft_strcmp("..", cmd->args[0]) == 0)
        _exec_cd(env,"..");
    else if (ft_strcmp("~", cmd->args[0]) == 0 || !cmd->args[0])
    {
        while (tmp)
        {
            if (ft_strcmp(tmp->key,"HOME") != 0)
            {
                printf("bash: cd: HOME not set\n");
                return ;
            }
            tmp = tmp->next;
        }
        free(tmp);
        _exec_cd(env,getenv("HOME"));
    }
    else
        _exec_cd(env,cmd->args[0]);
    return ;
}