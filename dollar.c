/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:16:27 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/28 09:57:17 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern struct t_global_status	g_exit;

size_t	calculate_required_length(const char *input)
{
	size_t		total_length;
	const char	*start;
	size_t		var_name_length;
	char		*var_name;
	char		*var_value;

	total_length = 0;
	while (*input)
	{
		if (*input == '$')
		{
			input++;
			start = input;
			while (*input && (my_isalnum(*input) || *input == '_'))
				input++;
			var_name_length = input - start;
			var_name = malloc(var_name_length + 1);
			if (!var_name)
			{
				perror("malloc");
				exit(1);
			}
			strncpy(var_name, start, var_name_length);
			var_name[var_name_length] = '\0';
			var_value = getenv(var_name);
			if (var_value)
				total_length += my_strlen(var_value);
			free(var_name);
		}
		else
		{
			total_length++;
			input++;
		}
	}
	return (total_length);
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
		if (!is_escaped && *input == '\'' && quote_char != '"')
		{
			if (quote_char == '\'')
				quote_char = '\0';
			else
				quote_char = '\'';
		}
		else if (!is_escaped && *input == '"' && quote_char != '\'')
		{
			if (quote_char == '"')
				quote_char = '\0';
			else
				quote_char = '"';
		}
		is_escaped = 0;
		input++;
	}
	return (quote_char == '\0');
}

char	*read_input_with_quotes(void)
{
	char	*line;
	size_t	len;
	ssize_t	read;
	char	*full_input;
	size_t	full_len;
	char	quote_char;
	int		is_escaped;
	size_t	i;

	line = NULL;
	len = 0;
	full_input = malloc(1);
	full_input[0] = '\0';
	full_len = 0;
	quote_char = '\0';
	is_escaped = 0;
	while ((read = getline(&line, &len, stdin)) != -1)
	{
		full_input = realloc(full_input, full_len + read + 1);
		my_strcat(full_input, line);
		full_len += read;
		if (full_input[full_len - 1] == '\n')
			full_input[full_len - 1] = '\0';
		for (i = 0; full_input[i] != '\0'; i++)
		{
			if (full_input[i] == '\\' && !is_escaped && (quote_char == '\"'
					|| quote_char == '\0'))
			{
				is_escaped = 1;
				continue ;
			}
			if ((full_input[i] == '"' || full_input[i] == '\'') && !is_escaped)
			{
				if (quote_char == full_input[i])
					quote_char = '\0';
				else if (quote_char == '\0')
					quote_char = full_input[i];
			}
			if (is_escaped)
				is_escaped = 0;
		}
		if (quote_char == '\0' && !is_escaped)
			break ;
		else
			printf("> ");
	}
	free(line);
	return (full_input);
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

char	*replace_env_vars(const char *input)
{
	size_t	required_length;
	char	*result;
	char	*current;
	char	quote_char;
	int		is_escaped;
	char	var_name[256];
	char	*var_start;
	char	*var_value;

	required_length = calculate_required_length(input);
	result = malloc(required_length + 1);
	// if (strstr(input,"echo"))
	// 	return ((char *)input);
	if (!result)
	{
		perror("malloc");
		exit(1);
	}
	current = result;
	quote_char = '\0';
	is_escaped = 0;
	while (*input)
	{
		if (*input == '\\' && quote_char == '"' &&
			(input[1] == '"' || input[1] == '\\' || input[1] == '$'))
		{
			*current++ = input[1];
			input += 2;
			continue ;
		}
		if (*input == '"' && quote_char != '\'')
		{
			if (!is_escaped && quote_char == '"')
				quote_char = '\0';
			else if (!is_escaped)
				quote_char = '"';
			input++;
			continue ;
		}
		if (*input == '\'' && quote_char != '"')
		{
			if (quote_char == '\'')
				quote_char = '\0';
			else
				quote_char = '\'';
			input++;
			continue ;
		}
		if (*input == '$' && quote_char != '\'')
		{
			input++;
			var_start = var_name;
			while (*input && (my_isalnum(*input) || *input == '_'))
				*var_start++ = *input++;
			*var_start = '\0';
			var_value = getenv(var_name);
			if (var_value)
			{
				strncpy(current, var_value, required_length - (current
							- result));
				current += strlen(var_value);
			}
			continue ;
		}
		if (*input != '\\')
			is_escaped = 0;
		*current++ = *input++;
	}
	*current = '\0';
	return (result);
}

int	checkdollar(char *str)
{
	int	i;
	// int flag;
	// int start;

	i = 0;
	// flag = 0;
	// start = 0;
	// int end = 0;
	if (strstr(str, "echo"))
	{
		while (str[i] != ' ')
			i++;
		i++;
		while (str[i])
		{
			// if (str[i] == '"')
			// {
			// 	flag = 1;
			// 	start = i;
			// }
			// while (str[i] != '"')
			// 	i++;
			// // printf("--------%c----------\n",str[i]);
			// if (str[i] == '"' && flag == 1)
			// {
			// 	int end = i;
			// 	char *qt = ft_substr(str,start,end);
			// 	printf("%s\n",qt);
			// }
			if (ft_cherchr(str, '"') == 1 && ft_cherchr(str, '|') == 1)
			{
				ft_strchr(str, '"');
				return (1);
			}
			
			// printf("%c",str[i]);
			i++;
		}
	}
	return (0);
}