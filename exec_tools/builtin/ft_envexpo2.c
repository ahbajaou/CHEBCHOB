/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envexpo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:41:51 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:35:16 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	checkexpo(char *key, char *value, t_list **env)
{
	t_list	*tmp;
	char	*j;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) != 0)
		{
			if (*value == 0)
				return (0);
			j = ft_join2(tmp->value, value);
			delet_unset(env, key);
			addback(env, key_value(key, j));
			free(j);
			return (0);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (1);
}

void	print_env(t_list **env, int flag)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (flag == 1 && tmp->key != NULL && tmp->value == NULL)
			printf("declare -x %s\n", tmp->key);
		if (flag == 0 && tmp->key != NULL && tmp->value != NULL)
			printf("%s=\"%s\"\n", tmp->key, tmp->value);
		if (flag == 1 && tmp->key != NULL && tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	free(tmp);
	return ;
}

int	checkjoin(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	check_double(t_list **env, char *key, char *value)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value)
			&& ft_strcmp(tmp->value, "NULL") != 0)
		{
			if (!value)
				return (0);
			delet_unset(env, key);
			addback(env, key_value(key, value));
			return (0);
		}
		if (ft_strcmp(tmp->key, key) == 0 && ft_strcmp(tmp->value, value) == 0)
			return (0);
		if (ft_strcmp(tmp->key, key) == 0 && value == NULL)
			return (0);
		tmp = tmp->next;
	}
	free(tmp);
	return (1);
}

char	*skipeq(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
		{
			i++;
			return (str + i);
		}
		i++;
	}
	return (str);
}
