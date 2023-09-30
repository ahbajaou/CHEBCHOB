/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 01:22:56 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/30 00:41:14 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd2(t_cmd *commands)
{
	int	i;

	if (commands->expo)
	{
		i = 0;
		while (commands->expo[i])
			i++;
		freesplitexpo(commands->expo);
	}
}

void	free_cmd3(t_cmd *commands)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = commands;
	while (temp)
	{
		next = temp->next;
		free_command(temp);
		temp = next;
	}
}

char	*strred(char *str)
{
	char	*continuation;

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
	return (str);
}

int	outdor_pars(char *str)
{
	int	flag;

	flag = 0;
	if (checkdollar(str) == 1)
		flag = 1;
	if (_exit_status(str) == 1)
		flag = 1;
	return (flag);
}

char	*space_in(char *replaced_str, char *str)
{
	(void)str;
	if (!replaced_str || my_strspn(replaced_str,
			" \t\n\r") == my_strlen(replaced_str))
	{
		if (replaced_str)
			free(replaced_str);
		return (NULL);
	}
	return (replaced_str);
}
