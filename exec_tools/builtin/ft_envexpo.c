/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envexpo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:39:00 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 02:18:45 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern struct t_global_status	g_exit;

char	*parsq(char *value)
{
	int	sz;

	if (!value)
		return (NULL);
	if (value[0] == '"' || value[0] == '\'')
	{
		sz = ft_len(value);
		value[sz - 1] = '\0';
		return (value + 1);
	}
	return (value);
}

void	expo_pars(char *str, char *str1, t_list **env)
{
	char	*value;
	int		sz;

	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
		|| str[0] == '"' || str[0] == '\'')
	{
		g_exit._exit = 1;
		printf("export : not a valid identifier : %s\n", str);
		return ;
	}
	value = parsq(str1);
	if (checkjoin(str) == 1)
	{
		sz = ft_len(str);
		str[sz - 1] = '\0';
		if (checkexpo(str, value, env) == 0)
			return ;
	}
	addback(env, key_value(str, value));
	return ;
}

char	*joinexpo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (skipeq(str + i, '='));
		if (str[i] == '=')
			return (skipeq(str + i, '='));
		i++;
	}
	return (NULL);
}

void	add_expo(char **str, t_list **env)
{
	int		i;
	char	**tmp;
	char	*pl;

	i = 0;
	(void)env;
	tmp = NULL;
	if (str[i][0] == '=')
	{
		printf("export : not a valid identifier : %s\n", str[i]);
		free4free(str);
		free(str);
		return ;
	}
	while (str[i])
	{
		pl = joinexpo(str[i]);
		tmp = ft_split(str[i], '=');
		if (check_double(env, tmp[0], pl))
			expo_pars(tmp[0], pl, env);
		i++;
	}
	free4free(tmp);
	free(tmp);
}

void	ft_env(t_list *env, t_cmd *cmd)
{
	int	flag;

	flag = -1;
	if (ft_strcmp(cmd->name, "export") == 0 && !cmd->expo[0])
		flag = 1;
	if (ft_strcmp(cmd->name, "env") == 0)
		flag = 0;
	if (flag == -1)
	{
		add_expo(cmd->expo, &env);
		return ;
	}
	if (flag == 0 || flag == 1)
	{
		print_env(&env, flag);
		return ;
	}
}
