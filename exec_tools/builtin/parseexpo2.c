/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexpo2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:00:32 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 17:15:05 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_strings2(const char *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*s != '\0')
	{
		if (*s == '"')
			flag = !flag;
		if (*s == c && !flag)
			count++;
		s++;
	}
	return (count + 1);
}

int	cnt_len(char *s, char c)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	while (s[len] != '\0')
	{
		if (s[len] == '"')
			flag = !flag;
		if (s[len] == c && !flag)
			break ;
		len++;
	}
	return (len);
}

char	*allocation_string2(const char *s, char c)
{
	int		len;
	char	*str;
	int		i;

	len = 0;
	i = 0;
	len = cnt_len((char *)s, c);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	**ft_free2(char **str, size_t i)
{
	while (i > 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
	return (NULL);
}
