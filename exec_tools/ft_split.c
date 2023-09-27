/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:32:58 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 18:04:26 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft__substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new;

	i = 0;
	if (start > ft_strlen((char *)s))
		return (strdup(""));
	while (i < len && s[i])
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

int	count_c(const char *str, char c, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		count++;
		i++;
	}
	return (count);
}

int	count_word(const char *str, char c)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i + 1] == c)
			|| (str[i] != c && str[i + 1] == '\0'))
			wd++;
		i++;
	}
	return (wd);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		sp;
	int		xc;
	char	**spl;
	int		x;

	sp = 0;
	i = 0;
	xc = count_word(s, c);
	spl = malloc(sizeof(char *) * (xc + 1));
	if (!spl)
		return (NULL);
	while (i < xc)
	{
		while (s[sp] && s[sp] == c)
			sp++;
		x = count_c(s, c, sp);
		spl[i] = ft__substr(s, sp, x);
		sp += x + 1;
		i++;
	}
	spl[i] = NULL;
	return (spl);
}
