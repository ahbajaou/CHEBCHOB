/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:45:26 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 02:39:13 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	splitexpofree(char **str, int i)
{
	if (!str[i])
	{
		ft_free2(str, i);
		return ;
	}
}

char	**splitexpo2(char **str, const char *s, char c, int i)
{
	int	flag;

	flag = 0;
	while (*s != '\0')
	{
		if (*s == '"')
			flag = !flag;
		while (*s != '\0' && *s == c && !flag)
			s++;
		if (*s != '\0')
		{
			str[i] = allocation_string2(s, c);
			splitexpofree(str, i);
			i++;
		}
		while (*s != '\0' && (*s != c || flag))
		{
			if (*s == '"')
				flag = !flag;
			s++;
		}
	}
	str[i] = NULL;
	return (str);
}

char	**splitexpo(const char *s, char c)
{
	char	**str;

	if (s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (count_strings2(s, c) + 1));
	if (!str)
		return (NULL);
	str = splitexpo2(str, s, c, 0);
	return (str);
}

void	freesplitexpo(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**parsexport(char *input)

{
	int		i;
	char	*str;
	char	**spl;

	i = 0;
	spl = NULL;
	if (!input)
		return (NULL);
	if (strstr(input, "export"))
	{
		while (input[i] != ' ' && input[i] != '\0')
			i++;
		str = strdup(input + i);
		spl = splitexpo(str, ' ');
		free(str);
		return (spl);
	}
	return (NULL);
}
