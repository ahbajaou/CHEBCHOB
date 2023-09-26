/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:15:39 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/25 12:04:06 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct global_status	g_exit;

void	free4free(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	tmp = NULL;
}
ev_list	*_env(char **envp)
{
	ev_list	*env;
	char	**tmp;
	int		i;

	env = NULL;
	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		addback(&env, key_value(tmp[0], tmp[1]));
		free4free(tmp);
		free(tmp);
		i++;
	}
	return (env);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit._exit = 130;
		printf("\n");
		printf("minishell: ");
	}
}


char *remove_double_quotes(const char *str)
{
    size_t len = strlen(str);

    if (str[0] == '"' && str[len - 1] == '"')
    {
        char *new_str = strndup(str + 1, len - 2);
        return new_str;
    }

    return strdup(str);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_cmd	*commands;
// 	ev_list	*env;
// 	char	*str;
// 	char	*old_str;
// 	char	*replaced_str;
// 	int		i;
// 	t_cmd	*temp;
// 	t_cmd	*next;

// 	(void)ac;
// 	(void)av;
// 	commands = NULL;
// 	env = _env(envp);
// 	signal(SIGINT, sighandler);
// 	signal(SIGQUIT, sighandler);
// 	while (1)
// 	{
// 		str = readline("minishell: ");
// 		if (!str)
// 			exit(1);
// 		add_history(str);
// 		// g_exit._exit = 0;
// 		// Gestion des guillemets non fermés
//         char *processed_str = remove_double_quotes(str);
// 	    free(str);
// 	    str = processed_str;

// 	    printf("%s\n", processed_str);
// 		while (!check_quotes(str))
// 		{
// 			char *continuation = readline("> "); // Prompt pour la continuation
// 			str = readline("minishell: ");
// 			if (str[0] == '\0')
// 			{
// 				free(str);
// 				continue ;
// 			}
// 			if (!str || strspn(str, " \t\n\r") == strlen(str))
// 			{
// 				free(str);
// 				continue ;
// 			}
// 			if (!continuation)
// 				break ;
// 			old_str = str;
// 			asprintf(&str, "%s\n%s", old_str, continuation);
// 				// Concaténez l'ancienne et la nouvelle entrée
// 			free(old_str);
// 			free(continuation);
// 		}
// 		replaced_str = replace_env_vars(str);
// 		if (!replaced_str || strspn(replaced_str,
// 				" \t\n\r") == strlen(replaced_str))
// 		{
// 			// free(str);
// 			if (replaced_str)
// 				// free(replaced_str);
// 			continue ;
// 		}
// 		commands = parse_input(replaced_str);
// 		commands->Expo = ParsExport(str);
//         if (strncmp(replaced_str, "echo", 4) == 0) 
//         {
//             // free(replaced_str);
//             // free(str);
//             continue;
//         }
// 		exec_cmd(commands, &env, envp);
// 		// print_commands(commands);
// 		free(replaced_str);
// 		free(str);
// 		if (commands->Expo)
// 		{
// 			i = 0;
// 			while (commands->Expo[i])
// 				i++;
// 			freeSplitExpo(commands->Expo);
// 		}
// 		temp = commands;
// 		while (temp)
// 		{
// 			next = temp->next;
// 			free_command(temp);
// 			temp = next;
// 		}
// 	}
// }

int ft_cherchr(char *str,char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
void ft_strchr(char *str , char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			char *skip = skipeq(str + i,'"');
			int sz = ft_len(skip);
			skip[sz - 1] = '\0';
			printf("%s\n",skip);
		}
		i++;
	}
}
int	checkdollar(char *str)
{
	// char **ego;
	int i = 0;
    if (strstr(str, "echo"))
    {
		while (str[i])
		{
			if (ft_cherchr(str,'"') == 1 &&  ft_cherchr(str,'|') == 1)
			{
				ft_strchr(str, '"');
				return (1);
			}
			i++;
		}
    }
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	t_cmd	*commands;
	ev_list	*env;
	char	*str;
	char	*old_str;
	char	*replaced_str;
	int		i;
	int flag = 0;
	// char **ecopars;
	// t_eco *eco;
	t_cmd	*temp;
	t_cmd	*next;

	(void)ac;
	(void)av;
	commands = NULL;
	// eco = NULL;
	env = _env(envp);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	while (1)
	{
		str = readline("minishell: ");
		if (!str)
			exit(1);
		add_history(str);

		while (!check_quotes(str))
		{
			char *continuation = readline("> ");
			if (!continuation)
				break;

			if (continuation[0] == '\0')
			{
				free(continuation);
				continue;
			}

			old_str = str;
			asprintf(&str, "%s\n%s", old_str, continuation);
			free(old_str);
			free(continuation);
		}
		if (checkdollar(str) == 1)
			flag = 1;
		if (_exit_status(str) == 1)
			flag = 1;
		char *processed_str = remove_double_quotes(str);
	    free(str);
	    str = processed_str;
		replaced_str = replace_env_vars(str);

		// Si la commande commence par "echo"
		// if (strncmp(replaced_str, "echo", 4) == 0 && ft_strchr(replaced_str) != 1) 
		// {
		//     printf("%s\n", replaced_str + 5);
		//     free(replaced_str);
		//     free(str);
		//     continue;  // Aller à la prochaine itération de la boucle
		// }

		if (!replaced_str || strspn(replaced_str, " \t\n\r") == strlen(replaced_str))
		{
			free(str);
			if (replaced_str)
				free(replaced_str);
			continue;
		}
        
		commands = parse_input(replaced_str);
		commands->Expo = ParsExport(str);
        // print_commands(commands);
		if (flag == 0)
			exec_cmd(commands, &env, envp);
		free(replaced_str);
		free(str);
		if (commands->Expo)
		{
			i = 0;
			while (commands->Expo[i])
				i++;
			freeSplitExpo(commands->Expo);
		}
		temp = commands;
		while (temp)
		{
			next = temp->next;
			free_command(temp);
			temp = next;
		}
	}
}
