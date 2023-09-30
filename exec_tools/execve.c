/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:36:58 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/30 02:01:45 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern struct t_global_status	g_exit;

int	errorve(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "exit") == 0)
		printf("exit\n");
	else if (ft_strcmp(cmd->name, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd->name, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		return (0);
	else if (((cmd->name[0] >= 'a' && cmd->name[0] <= 'z'))
		|| ((cmd->name[0] >= 'A' && cmd->name[0] <= 'Z'))
		|| (cmd->name[0] >= '0' && cmd->name[0] <= '9'))
	{
		error(ERROR_CNF, cmd);
		g_exit._exit = 127;
		return (0);
	}
	else
	{
		error(REDIR_ERROR, cmd);
		g_exit._exit = 2;
		return (0);
	}
	return (0);
}

char	*execve_cmd(t_cmd *cmd, t_list *env)
{
	char	**path;
	char	*p;

	path = get_path(env, cmd);
	p = access_ve(path, cmd);
	if (!p)
	{
		if (errorve(cmd) == 0)
			return (NULL);
		return (NULL);
	}
	if (!cmd || ft_cherchr(cmd->name, '?') || ft_cherchr(cmd->name, '/'))
		error(ERROR_CNF, cmd);
	return (p);
}
