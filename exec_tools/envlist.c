/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 09:59:37 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 01:13:53 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern struct t_global_status	g_exit;

t_list	*_env(char **envp)
{
	t_list	*env;
	char	**tmp;
	int		i;

	env = NULL;
	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		addback(&env, key_value(tmp[0], tmp[1]));
		free4free(tmp);
		free(tmp);
		i++;
	}
	return (env);
}

int	ft_cherchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit._exit = 130;
		printf("\n");
		printf("minishell: ");
	}
}
