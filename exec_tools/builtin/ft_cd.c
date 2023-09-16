
#include "../../minishell.h"

void    update_path(ev_list *env, char *old,char *path,char *new)
{
    ev_list *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(old, tmp->key) == 0)
            tmp->value = ft__strdup(new);
        if (ft_strcmp(path, tmp->key) == 0)
            tmp->value = ft__strdup(new);
        tmp = tmp->next;
    }
    free(tmp);
}

void _exec_cd(ev_list *env,char *name)
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_path(env,"OLDPWD",NULL,cwd);
    chdir(name);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        update_path(env,NULL,"PWD",cwd);
}
void    ft_cd(t_cmd *cmd, ev_list *env)
{
    if (ft_strcmp("..", cmd->args[0]) == 0)
        _exec_cd(env,"..");
    else if (ft_strcmp("~", cmd->args[0]) == 0 || !cmd->args[0])
        _exec_cd(env,getenv("HOME"));
    else
        _exec_cd(env,cmd->args[0]);
 
}