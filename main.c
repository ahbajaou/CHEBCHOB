

#include "minishell.h"

ev_list	*_env(char **envp)
{
    ev_list *env = NULL;

    char **tmp = NULL;

    int i = 0;
    while (envp[i])
    {
        tmp = ft_split(envp[i], '=');
        addback(&env,key_value(tmp[0], tmp[1]));
        i++;
    }
    free(tmp);
    return(env);
}

int main(int ac,char **av,char **envp)
{
    (void)ac;
    (void)av;
    ev_list *env = _env(envp);

    while(1)
    {
        char *str = readline("minishell: ");
        if (!str)
            exit(1);
        add_history(str);
        t_cmd *commands = parse_input(str);
        print_commands(commands);
        exec_cmd(commands,&env);
    }
    return 0;
}