/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 03:52:41 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:27:39 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*custom(char *str, char *delims, char **saveptr)
{
	char	*token_start;

	if (!str)
		str = *saveptr;
	while (*str && strchr(delims, *str))
		str++;
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	token_start = str;
	while (*str && !strchr(delims, *str))
		str++;
	if (*str == '\0')
		*saveptr = str;
	else
	{
		*str = '\0';
		*saveptr = str + 1;
	}
	return (token_start);
}

char	*custom_str(char *str, char *delims)
{
	static char	*next_token;
	char		*token_start;

	next_token = NULL;
	if (!str)
		str = next_token;
	while (*str && strchr(delims, *str))
		str++;
	if (*str == '\0')
	{
		next_token = str;
		return (NULL);
	}
	token_start = str;
	while (*str && !strchr(delims, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		next_token = str + 1;
	}
	else
		next_token = str;
	return (token_start);
}

char	*remove_double_quotes(const char *str)
{
	size_t	len;
	char	*new_str;

	len = my_strlen(str);
	if (str[0] == '"' && str[len - 1] == '"')
	{
		new_str = strndup(str + 1, len - 2);
		return (new_str);
	}
	return (strdup(str));
}
