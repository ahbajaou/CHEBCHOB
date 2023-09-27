/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:43:53 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/27 20:50:50 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern struct t_global_status	g_exit;

int	errerexit3(t_cmd *cmd, int i)
{
	if (((cmd->args[i][0] >= 'a' && cmd->args[i][0] <= 'z') && i == 0) ||
		((cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z') && i == 0))
	{
		printf("exit: %s: numeric argument required\n", cmd->args[i]);
		exit(0);
	}
	return (0);
}

int	errerexit2(t_cmd *cmd, int i)
{
	int	j;
	int	m;

	j = 0;
	m = 0;
	while (cmd->args[i][j])
	{
		if (cmd->args[i][j] == '-')
		{
			m++;
			break ;
		}
		if (m > 1)
		{
			printf("exit: %s: numeric argument required\n", cmd->args[i]);
			return (1);
		}
		j++;
	}
	return (0);
}

int	errexit(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		errerexit3(cmd, i);
		errerexit2(cmd, i);
		i++;
	}
	if (i > 1)
	{
		g_exit._exit = 1;
		printf("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

void	ft_exit(t_cmd *cmd)
{
	(void)cmd;
	exit(1);
}
