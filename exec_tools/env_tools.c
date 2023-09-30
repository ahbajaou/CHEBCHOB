/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:34:53 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 00:46:14 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft__strdup(char *str)
{
	int		i;
	char	*dup;

	if (!str)
		return (NULL);
	i = strlen(str);
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

t_list	*key_value(char *key, char *value)
{
	t_list	*env;

	env = malloc(sizeof(t_list));
	env->key = ft__strdup(key);
	env->value = ft__strdup(value);
	env->next = NULL;
	return (env);
}

void	addback(t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = *list;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	sigcmd(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sigchild(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
