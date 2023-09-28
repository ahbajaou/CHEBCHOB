/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:15:39 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/28 10:01:11 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern struct t_global_status	g_exit;

char	*concatenate_with_newline(char *old_str, char *continuation)
{
	size_t	old_str_len;
	size_t	continuation_len;
	size_t	new_str_size;
	size_t	i;
	size_t	j;
	char	*new_str;

	old_str_len = strlen(old_str);
	continuation_len = strlen(continuation);
	new_str_size = old_str_len + continuation_len + 2;
	new_str = malloc(new_str_size);
	if (!new_str)
		exit(1);
	i = 0;
	j = 0;
	while (i < old_str_len)
	{
		new_str[j] = old_str[i];
		i++;
		j++;
	}
	new_str[j] = '\n';
	j++;
	i = 0;
	while (i < continuation_len)
	{
		new_str[j] = continuation[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(old_str);
	return (new_str);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*commands;
	t_list	*env;
	char	*str;
	char	*replaced_str;
	int		i;
	int		flag;
	t_cmd	*temp;
	t_cmd	*next;
	char	*continuation;
	char	*processed_str;

	(void)ac;
	(void)av;
	commands = NULL;
	env = _env(envp);
	signal(SIGINT, sighandler);
	while (1)
	{
		flag = 0;
		signal(SIGQUIT, SIG_DFL);
		str = readline("minishell: ");
		if (!str)
			exit(1);
		add_history(str);
		while (!check_quotes(str))
		{
			continuation = readline("> ");
			if (!continuation)
				break ;
			if (continuation[0] == '\0')
			{
				free(continuation);
				continue ;
			}
			str = concatenate_with_newline(str, continuation);
			free(continuation);
		}
		if (checkdollar(str) == 1)
			flag = 1;
		if (_exit_status(str) == 1)
			flag = 1;
		processed_str = remove_double_quotes(str);
		free(str);
		str = processed_str;
		replaced_str = replace_env_vars(str);
		if (!replaced_str || my_strspn(replaced_str,
				" \t\n\r") == my_strlen(replaced_str))
		{
			free(str);
			if (replaced_str)
				free(replaced_str);
			continue ;
		}
		commands = parse_input(replaced_str);
		commands->expo = parsexport(str);
		// print_commands(commands);
		if (flag == 0)
			exec_cmd(commands, &env, envp, 0);
		free(replaced_str);
		free(str);
		if (commands->expo)
		{
			i = 0;
			while (commands->expo[i])
				i++;
			freesplitexpo(commands->expo);
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

