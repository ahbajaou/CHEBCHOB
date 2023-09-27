/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:48:51 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:36:41 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parentbuilt(t_cmd *cmd, t_list **env)
{
	if (ft_strcmp("cd", cmd->name) == 0)
	{
		ft_cd(cmd, env);
		return ;
	}
}

int	checkbuilt(t_cmd *cmd, t_list **env)
{
	if (ft_strcmp("unset", cmd->name) == 0)
	{
		ft_unset(env, cmd);
		return (1);
	}
	if (ft_strcmp("exit", cmd->name) == 0)
	{
		ft_exit(cmd);
		return (1);
	}
	if (ft_strcmp("env", cmd->name) == 0)
	{
		ft_env(*env, cmd);
		return (1);
	}
	if (ft_strcmp("export", cmd->name) == 0)
	{
		ft_env(*env, cmd);
		return (1);
	}
	if (ft_strcmp("cd", cmd->name) == 0)
		return (1);
	return (0);
}

int	check_builting(t_cmd *cmd, t_list **env)
{
	if (ft_strcmp("echo", cmd->name) == 0)
	{
		ft_echo(cmd);
		return (1);
	}
	if (ft_strcmp("pwd", cmd->name) == 0)
	{
		ft_pwd(*env);
		return (1);
	}
	return (0);
}
