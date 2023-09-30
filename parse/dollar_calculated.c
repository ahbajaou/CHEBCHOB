/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_calculated.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:36:18 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:24:49 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocate_new_str(t_cmd *data)
{
	size_t	new_str_size;
	char	*new_str;

	data->old_str_len = strlen(data->old_str);
	data->continuation_len = strlen(data->continuation);
	new_str_size = data->old_str_len + data->continuation_len + 2;
	new_str = malloc(new_str_size);
	if (!new_str)
		exit(1);
	return (new_str);
}

void	copy_strs_to_new(char *new_str, t_cmd *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < data->old_str_len)
		new_str[j++] = data->old_str[i++];
	new_str[j++] = '\n';
	i = 0;
	while (i < data->continuation_len)
		new_str[j++] = data->continuation[i++];
	new_str[j] = '\0';
}

char	*concatenate_with_newline(char *old_str, char *continuation)
{
	t_cmd	data;
	char	*new_str;

	data.old_str = old_str;
	data.continuation = continuation;
	new_str = allocate_new_str(&data);
	copy_strs_to_new(new_str, &data);
	free(old_str);
	return (new_str);
}

void	update_quote_state(char current, char *quote_char, int is_escaped)
{
	if (!is_escaped && current == '\'' && *quote_char != '"')
	{
		if (*quote_char == '\'')
			*quote_char = '\0';
		else
			*quote_char = '\'';
	}
	else if (!is_escaped && current == '"' && *quote_char != '\'')
	{
		if (*quote_char == '"')
			*quote_char = '\0';
		else
			*quote_char = '"';
	}
}

int	check_quotes(const char *input)
{
	char	quote_char;
	int		is_escaped;

	quote_char = '\0';
	is_escaped = 0;
	while (*input)
	{
		if (*input == '\\' && (input[1] == '"' || input[1] == '\''))
		{
			is_escaped = 1;
			input += 2;
			continue ;
		}
		update_quote_state(*input, &quote_char, is_escaped);
		is_escaped = 0;
		input++;
	}
	return (quote_char == '\0');
}
