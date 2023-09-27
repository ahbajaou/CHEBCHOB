/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:47:47 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:34:20 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delet_unset2(t_list *tmp, t_list **env)
{
	tmp = (*env);
	(*env) = (*env)->next;
	free(tmp->key);
	free(tmp->value);
	return ;
}

void	delet_unset(t_list **env, char *key)
{
	t_list	*tmp;
	t_list	*perv;

	tmp = *env;
	if (env != NULL)
	{
		if (ft_strcmp(tmp->key, key) != 0)
		{
			while (tmp->next)
			{
				if (ft_strcmp(tmp->next->key, key) == 0)
				{
					perv = tmp->next;
					free(tmp->next->key);
					free(tmp->next->value);
					tmp->next = tmp->next->next;
					free(perv);
					return ;
				}
				tmp = tmp->next;
			}
		}
		else
			delet_unset2(tmp, env);
	}
}

void	ft_unset(t_list **env, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		delet_unset(env, cmd->args[i]);
		i++;
	}
}
