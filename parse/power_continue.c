/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_continue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 03:57:26 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:25:56 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection(char **token, char **lasts, t_cmd *current)
{
	char	*redirection;

	redirection = *token;
	*token = custom(NULL, " ", lasts);
	if (*token && (*token[0] == '>' || *token[0] == '<'))
	{
		my_strcat(redirection, *token);
		*token = custom(NULL, " ", lasts);
	}
	if (!*token)
	{
		error(REDIR_ERROR, NULL);
		return ;
	}
	if (my_strcmp(redirection, ">") == 0)
		add_redirection(current, *token, REDIR_OUTPUT);
	else if (my_strcmp(redirection, "<") == 0)
		add_redirection(current, *token, REDIR_INPUT);
	else if (my_strcmp(redirection, ">>") == 0)
		add_redirection(current, *token, REDIR_APPEND);
	else if (my_strcmp(redirection, "<<") == 0)
		add_redirection(current, *token, REDIR_HEREDOC);
}

void	handle_pipe(char **token, char **lasts, t_cmd **current)
{
	t_cmd	*new_command;

	*token = custom(NULL, " ", lasts);
	new_command = create_command(*token);
	(*current)->next = new_command;
	*current = new_command;
}

// t_cmd	*parse_input(char *input)
// {
// 	t_cmd	*head;
// 	t_cmd	*current;
// 	char	*token;
// 	char	*lasts;

// 	if (!input || my_strlen(input) == 0)
// 		return (NULL);
// 	token = custom(input, " ", &lasts);
// 	if (!token)
// 		return (NULL);
// 	head = NULL;
// 	current = NULL;
// 	while (token != NULL)
// 	{
// 		if (!token || my_strlen(token) == 0 || my_strspn(token,
// 				" \t\n\r") == my_strlen(token))
// 		{
// 			token = custom(NULL, " ", &lasts);
// 			continue ;
// 		}
// 		if (!current)
// 		{
// 			current = create_command(NULL);
// 			if (!head)
// 				head = current;
// 		}
// 		if (token && my_strcmp(token, "|") == 0)
// 			handle_pipe(&token, &lasts, &current);
// 		else if (token && (token[0] == '>' || token[0] == '<'))
// 			handle_redirection(&token, &lasts, current);
// 		else
// 		{
// 			if (head == NULL)
// 			{
// 				head = create_command(token);
// 				current = head;
// 			}
// 			else
// 			{
// 				if (current->name == NULL)
// 				{
// 					if (current->name)
// 						free(current->name);
// 					current->name = my_strdup(token);
// 				}
// 				else
// 					add_argument(current, token);
// 			}
// 		}
// 		token = custom(NULL, " ", &lasts);
// 	}
// 	return (head);
// }
