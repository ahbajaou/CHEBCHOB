

#include "minishell.h"

void    free4free(char **tmp)
{
    int i = 0;
    while (tmp[i])
    {
        free(tmp[i]);
        i++;
    }
    tmp = NULL;
}
ev_list	*_env(char **envp)
{
    ev_list *env = NULL;

    char **tmp = NULL;

    int i = 0;
    while (envp[i])
    {
        tmp = ft_split(envp[i], '=');
        addback(&env,key_value(tmp[0], tmp[1]));
        free4free(tmp);
        free(tmp);
        i++;
    }
    return(env);
}

void    sighandler(int sig)
{
    if (sig == SIGINT)
        printf("\nminishell: ");
    // if (sig == SIGQUIT)
    //     exit(1);
}
int main(int ac,char **av,char **envp)
{
    (void)ac;
    (void)av;

    t_cmd *commands = NULL;
    ev_list *env = _env(envp);
    signal(SIGINT,sighandler);
    while(1)
    {
        // signal(SIGQUIT,sighandler);
        printf("---------------------------------\n");
        char *str = readline("minishell: ");
        if (!str)
            exit(1);
        if (str[0] == '\0')
        {
            free(str);
            continue;
        }
        add_history(str);

        // Gestion des guillemets non fermés
        while (!check_quotes(str))
        {
            char *continuation = readline("> ");  // Prompt pour la continuation
            if (!continuation)
                break;
            char *old_str = str;
            asprintf(&str, "%s\n%s", old_str, continuation);  // Concaténez l'ancienne et la nouvelle entrée
            free(old_str);
            free(continuation);
        }

        char* replaced_str = replace_env_vars(str);
        if (!replaced_str)
        {
            free(str);
            continue;  // Si replace_env_vars renvoie NULL, ignorez le reste du traitement
        }
        commands = parse_input(replaced_str);
        print_commands(commands);
        exec_cmd(commands, &env, envp);
        free(replaced_str);
        free(str);
        free(commands->name);
        free(commands);
    }
}
