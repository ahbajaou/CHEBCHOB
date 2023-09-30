/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 03:58:48 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:25:59 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free4free(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
}

void	free_redirection_list(t_redirection_list *head)
{
	t_redirection_list	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->filename)
			free(temp->filename);
		free(temp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	i = 0;
	while (cmd->args && i < cmd->arg_count)
	{
		if (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}
		i++;
	}
	if (cmd->args)
	{
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->redirection_file)
		free(cmd->redirection_file);
	free(cmd);
}

void	free_command(t_cmd *command)
{
	int	i;

	i = -1;
	if (!command)
		return ;
	if (command->name)
	{
		free(command->name);
		command->name = NULL;
	}
	while (command->args && ++i < command->arg_count)
	{
		if (command->args[i])
			free(command->args[i]);
	}
	if (command->args)
	{
		free(command->args);
		command->args = NULL;
	}
	if (command->redirection_file)
		free(command->redirection_file);
	if (command->redirections)
		free_redirection_list(command->redirections);
	free(command);
}
