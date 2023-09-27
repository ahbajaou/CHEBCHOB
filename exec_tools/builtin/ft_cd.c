/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:55:05 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:35:57 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_path(t_list *env, char *old, char *new)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp("PWD", tmp->key) == 0 && new != NULL)
		{
			free(tmp->value);
			tmp->value = ft__strdup(new);
		}
		if (ft_strcmp("OLDPWD", tmp->key) == 0 && old != NULL)
		{
			free(tmp->value);
			tmp->value = ft__strdup(old);
		}
		tmp = tmp->next;
	}
	free(tmp);
}

void	_exec_cd(t_list **env, char *name)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_path(*env, cwd, NULL);
	chdir(name);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_path(*env, NULL, cwd);
}

char	*_getenv(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	free(tmp);
	return (NULL);
}

void	ft_cd(t_cmd *cmd, t_list **env)
{
	char	*path;

	if (ft_strcmp("..", cmd->args[0]) == 0)
		_exec_cd(env, cmd->args[0]);
	else if (ft_strcmp("~", cmd->args[0]) == 0 || !cmd->args[0])
	{
		path = _getenv(env);
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
		_exec_cd(env, path);
	}
	else
		_exec_cd(env, cmd->args[0]);
	return ;
}
