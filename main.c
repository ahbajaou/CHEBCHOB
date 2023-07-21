

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
    // int e_exit = 0;
    // t_cmd *cmd;
    // cmd = NULL;
    ev_list *env = _env(envp);

    t_cmd *commands = NULL;
    (void)env;
    while(1)
    {
        char *str = readline("minishell: ");
        if (!str)
            exit(1);
        if (str[0] == '\0')
        {
            free(str);
            continue;
        }
        add_history(str);
        commands = parse_input(str);
        print_commands(commands);
        exec_cmd(commands,&env,envp);
        // printf("--%s---\n",commands->args[0]);
    }
    return 0;
}