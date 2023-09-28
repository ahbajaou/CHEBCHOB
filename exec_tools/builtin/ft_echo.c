/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:00:42 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/09/28 09:57:01 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_echo(char **str, int i, int flag)
{
	char	*tmp;

	tmp = NULL;
	while (str[i])
	{
		tmp = ft_join2(tmp, str[i]);
		if (str[i + 1] != NULL)
			tmp = ft_join2(tmp, " ");
		i++;
	}
	printf("%s", tmp);
	free(tmp);
	if (flag == 1)
		printf("\n");
	return ;
}

int	handel_n2(char **str, int i, int flag, int j)
{
	if (str[i][0] == '-' && str[i][1] != 'n')
	{
		print_echo(str, i, flag);
		return (0);
	}
	if ((j == 0 && str[i][j] != '-'))
	{
		print_echo(str, i, flag);
		return (0);
	}
	return (1);
}

int	handel_n3(char **str, int i, int j)
{
	if (str[i][j] != 'n' || str[i][j] != 0)
	{
		if (str[i][j] != 0)
		{
			print_echo(str, i, 0);
			return (0);
		}
	}
	return (1);
}

int	handel_n(char **str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 1;
	while (str[i])
	{
		j = 0;
		if (handel_n2(str, i, flag, j) == 0)
			return (0);
		j++;
		while (str[i][j] == 'n')
			j++;
		if (handel_n3(str, i, j) == 1)
			flag = 0;
		if (str[i + 1] == NULL)
			flag = 0;
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	if (handel_n(cmd->args) != 1)
		exit(0);
}
