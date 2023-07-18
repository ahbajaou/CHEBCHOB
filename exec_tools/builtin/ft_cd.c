
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
void    ft_cd(t_cmd *cmd, ev_list *env)
{
 
    char cwd[256];

        if (ft_strcmp("cd", cmd->name) == 0 && !cmd->args)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,"OLDPWD",NULL,cwd);
            chdir("..");
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,NULL,"PWD",cwd);
        }
        else
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,"OLDPWD",NULL,cwd);
            chdir(cmd->args[0]);
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                update_path(env,NULL,"PWD",cwd);
        }
 
}