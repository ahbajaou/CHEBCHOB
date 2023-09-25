#include "minishell.h"

extern struct global_status g_exit;


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
    {
        printf("\n");
        printf("minishell: ");
    }
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
    signal(SIGQUIT,sighandler);

    while(1)
    {
        char *str = readline("minishell: ");
        if (!str)
            exit(1);
        add_history(str);
        // g_exit._exit = 0;

        // Gestion des guillemets non fermés
        while (!check_quotes(str))
        {
            char *continuation = readline("> ");  // Prompt pour la continuation
            char *str = readline("minishell: ");
            if (str[0] == '\0')
            {
                free(str);
                continue;
            }
            if (!str || strspn(str, " \t\n\r") == strlen(str))
            {
                free(str);
                continue;
            }
            if (!continuation)
                break;
            char *old_str = str;
            asprintf(&str, "%s\n%s", old_str, continuation);  // Concaténez l'ancienne et la nouvelle entrée
            free(old_str);
            free(continuation);
        }
        char* replaced_str = replace_env_vars(str);
       if (!replaced_str || strspn(replaced_str, " \t\n\r") == strlen(replaced_str))
        {
            free(str);
            if (replaced_str) free(replaced_str);
            continue;
        }
        commands = parse_input(replaced_str);
        commands->Expo = ParsExport(str);
        exec_cmd(commands, &env, envp);
        // print_commands(commands);
        free(replaced_str);
        free(str);
        if (commands->Expo)
        {
            int i = 0;
            while (commands->Expo[i])
                i++;
            freeSplitExpo(commands->Expo);
        }
        t_cmd* temp = commands;
        while (temp) 
        {
            t_cmd* next = temp->next;
            free_command(temp);
            temp = next;
        }
    }
}
