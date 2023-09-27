/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:36:58 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/26 20:18:53 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern struct global_status	g_exit;

char	*execve_cmd(t_cmd *cmd, ev_list *env)
{
	char	**path;
	char	*p;

	path = get_path(env, cmd);
	p = access_ve(path, cmd);
	if (!p)
	{
		if (ft_strcmp(cmd->name, "exit") == 0)
			printf("exit\n");
		else if (ft_strcmp(cmd->name, "cd") == 0)
			return (NULL);
		else if (ft_strcmp(cmd->name, "export") == 0)
			return (NULL);
		else if (ft_strcmp(cmd->name, "unset") == 0)
			return (NULL);
		else if (((cmd->name[0] >= 'a' && cmd->name[0] <= 'z'))
				|| ((cmd->name[0] >= 'A' && cmd->name[0] <= 'Z'))
				|| (cmd->name[0] >= '0' && cmd->name[0] <= '9'))
		{
			error(ERROR_CNF, cmd);
			g_exit._exit = 127;
			return (NULL);
		}
		else
		{
			error(REDIR_ERROR, cmd);
			g_exit._exit = 2;
			return (NULL);
		}
		return (NULL);
	}
	return (p);
}
