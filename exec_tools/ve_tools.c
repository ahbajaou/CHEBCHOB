/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ve_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:52:05 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:36:57 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_list *env, t_cmd *cmd)
{
	t_list	*tmp;
	char	*path;
	char	**spl;

	(void)cmd;
	tmp = (env);
	path = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			path = ft__strdup(tmp->value);
		tmp = tmp->next;
	}
	if (!path)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	spl = ft_split(path, ':');
	free(path);
	free(tmp);
	tmp = NULL;
	return (spl);
}

char	*access_ve(char **path, t_cmd *cmd)
{
	int		i;
	char	*current;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		current = ft_join2(path[i], "/");
		current = ft_join2(current, cmd->name);
		if (!access(current, F_OK))
		{
			free4free(path + i + 1);
			free(path);
			return (current);
		}
		free(current);
		i++;
	}
	free(path);
	return (NULL);
}
