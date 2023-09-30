/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 07:15:47 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:26:08 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_command(char *name)
{
	t_cmd	*command;

	command = my_calloc(1, sizeof(t_cmd));
	if (!command)
		exit(1);
	if (name != NULL)
	{
		command->name = my_strdup(name);
		if (!command->name)
		{
			free(command);
			exit(1);
		}
	}
	else
		command->name = NULL;
	command->args = malloc(sizeof(char *));
	command->args[0] = NULL;
	command->arg_count = 0;
	command->redirection = REDIR_NONE;
	command->redirection_file = NULL;
	command->next = NULL;
	return (command);
}

void	add_argument(t_cmd *command, char *arg)
{
	size_t	current_size;
	size_t	new_size;

	current_size = (command->arg_count + 1) * sizeof(char *);
	new_size = (command->arg_count + 2) * sizeof(char *);
	command->args = my_realloc(command->args, current_size, new_size);
	if (!command->args)
	{
		printf("Erreur d'allocation de mémoire.\n");
		exit(1);
	}
	command->args[command->arg_count] = my_strdup(arg);
	command->arg_count++;
	command->args[command->arg_count] = NULL;
}

void	set_redirection(t_cmd *command, char *filename,
		t_redirection redirection)
{
	add_redirection(command, filename, redirection);
}

void	add_redirection(t_cmd *command, char *filename,
		t_redirection redirection)
{
	t_redirection_list	*new_redir;
	t_redirection_list	*temp;

	new_redir = calloc(1, sizeof(t_redirection_list));
	new_redir->redirection_type = redirection;
	new_redir->filename = my_strdup(filename);
	new_redir->next = NULL;
	if (!command->redirections)
		command->redirections = new_redir;
	else
	{
		temp = command->redirections;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

// void	print_commands(t_cmd *head)
// {
// 	t_cmd				*current;
// 	int					i;
// 	t_redirection_list	*temp;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		i = 0;
// 		printf("Command: %s\n", current->name);
// 		while (i < current->arg_count)
// 		{
// 			printf("Argument: %s\n", current->args[i]);
// 			i++;
// 		}
// 		if (current->redirections)
// 		{
// 			temp = current->redirections;
// 			while (temp)
// 			{
// 				printf("Redirection: ");
// 				if (temp->redirection_type == REDIR_INPUT)
// 					printf("< ");
// 				else if (temp->redirection_type == REDIR_OUTPUT)
// 					printf("> ");
// 				else if (temp->redirection_type == REDIR_APPEND)
// 					printf(">> ");
// 				else if (temp->redirection_type == REDIR_HEREDOC)
// 					printf("<< ");
// 				printf("%s\n", temp->filename);
// 				temp = temp->next;
// 			}
// 		}
// 		current = current->next;
// 	}
// }
