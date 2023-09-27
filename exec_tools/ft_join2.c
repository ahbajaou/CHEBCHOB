/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 03:17:21 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/26 20:19:25 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_slen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_join2(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(ft_slen(s1) + ft_slen(s2) + 1);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	if (s2)
	{
		while (s2[j])
			str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

char	*ft_join3(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = malloc(ft_slen(s1) + ft_slen(s2) + 1);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	if (s2)
	{
		while (s2[j])
			str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}
