/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:59:38 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:43:36 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern struct t_global_status	g_exit;

void	errcd(t_cmd *cmd)
{
	if (!cmd->args[0])
		return ;
	if (chdir(cmd->args[0]))
	{
		g_exit._exit = 127;
		printf("%s No such file or directory\n", cmd->args[0]);
	}
}

void	getpath2(t_cmd *cmd, int p, int i, char **spl)
{
	if (ft_strcmp(cmd->name, "./Makefile") == 0)
	{
		g_exit._exit = 126;
		printf("permission denied\n");
	}
	else if (ft_strcmp(spl[p - 1], cmd->name + i) != 0)
		error(ERROR_DOC, cmd);
	else
	{
		g_exit._exit = 126;
		printf("%s : : Is a directory\n", cmd->name + i);
	}
}

void	getpath(t_cmd *cmd, t_list *env, int i)
{
	t_list	*tmp;
	int		p;
	char	**spl;

	p = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			spl = ft_split(tmp->value, '/');
		tmp = tmp->next;
	}
	while (spl[p])
		p++;
	getpath2(cmd, p, i, spl);
	free4free(spl);
	free(spl);
	free(tmp);
}

void	erredoc(t_cmd *cmd, t_list *env)
{
	int	i;

	(void)cmd;
	(void)env;
	i = 0;
	while (cmd->name[i] == '.' || cmd->name[i] == '/')
		i++;
	getpath(cmd, env, i);
}

int	checkerrer(t_cmd *cmd, t_list *env)
{
	if (cmd->name)
	{
		if (ft_strcmp(cmd->name, "exit") == 0)
		{
			if (errexit(cmd) == 1)
				return (1);
			return (0);
		}
		else if (strstr(cmd->name, "../")
			|| ft_strcmp(cmd->name, "./Makefile") == 0)
		{
			erredoc(cmd, env);
			return (0);
		}
		else if (ft_strcmp(cmd->name, "export") == 0)
			return (0);
		else if (ft_strcmp(cmd->name, "env") == 0)
			return (0);
		else if (ft_strcmp(cmd->name, "unset") == 0)
			return (0);
	}
	return (1);
}
