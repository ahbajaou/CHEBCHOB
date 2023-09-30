/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 03:53:25 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:25:39 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'))
		return (1);
	return (0);
}

void	*my_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	char	*ptr;
	size_t	i;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

void	*my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	copy_size;
	size_t	i;
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	i = -1;
	while (++i < copy_size)
		((char *)new_ptr)[i] = ((char *)ptr)[i];
	free(ptr);
	return (new_ptr);
}

void	ft_strchr(char *str, char c)
{
	int		i;
	char	*skip;
	int		sz;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			skip = skipeq(str + i, '"');
			sz = ft_len(skip);
			skip[sz - 1] = '\0';
			printf("%s\n", skip);
		}
		i++;
	}
}
