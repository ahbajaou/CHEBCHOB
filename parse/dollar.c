/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:16:27 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/30 03:02:46 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern struct t_global_status	g_exit;

static size_t	get_var_length(const char **input)
{
	size_t		length;
	const char	*start;
	char		*var_name;
	char		*var_value;

	start = *input;
	while (**input && (my_isalnum(**input) || **input == '_'))
		(*input)++;
	length = *input - start;
	var_name = malloc(length + 1);
	if (!var_name)
		return (0);
	strncpy(var_name, start, length);
	var_name[length] = '\0';
	var_value = getenv(var_name);
	free(var_name);
	if (var_value)
		return (my_strlen(var_value));
	else
		return (0);
}

size_t	calculate_required_length(const char *input)
{
	size_t	total_length;

	total_length = 0;
	while (*input)
	{
		if (*input == '$')
		{
			input++;
			total_length += get_var_length(&input);
		}
		else
		{
			total_length++;
			input++;
		}
	}
	return (total_length);
}

int	_exit_status(char *input)
{
	int	i;

	i = 0;
	if (strstr(input, "echo"))
	{
		while (input[i])
		{
			if (ft_cherchr(input, '$') == 1 && ft_cherchr(input, '?') == 1)
			{
				printf("%d\n", g_exit._exit);
				g_exit._exit = 0;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	checkdollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (strstr(str, "echo"))
	{
		while (str[i] != ' ')
			i++;
		i++;
		while (str[i])
		{
			if (ft_cherchr(str, '"') == 1 && ft_cherchr(str, '|') == 1)
			{
				ft_strchr(str, '"');
				return (1);
			}
			i++;
		}
	}
	return (0);
}
