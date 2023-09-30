/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_on.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:05 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:26:04 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_current_and_head(t_cmd **current, t_cmd **head)
{
	*current = create_command(NULL);
	if (!*head)
		*head = *current;
}

void	process_token(char **token, char **lasts, t_cmd **current, t_cmd **head)
{
	if (*token && my_strcmp(*token, "|") == 0)
		handle_pipe(token, lasts, current);
	else if (*token && ((*token)[0] == '>' || (*token)[0] == '<'))
		handle_redirection(token, lasts, *current);
	else
	{
		if (*head == NULL)
		{
			*head = create_command(*token);
			*current = *head;
		}
		else
		{
			if (!(*current)->name)
			{
				if ((*current)->name)
					free((*current)->name);
				(*current)->name = my_strdup(*token);
			}
			else
				add_argument(*current, *token);
		}
	}
}

t_cmd	*parse_input(char *input)
{
	t_cmd	*head;
	t_cmd	*current;
	char	*token;
	char	*lasts;

	if (!input || my_strlen(input) == 0)
		return (NULL);
	token = custom(input, " ", &lasts);
	if (!token)
		return (NULL);
	head = NULL;
	current = NULL;
	while (token != NULL)
	{
		if (!token || my_strlen(token) == 0 || my_strspn(token,
				" \t\n\r") == my_strlen(token))
			token = custom(NULL, " ", &lasts);
		if (!current)
			initialize_current_and_head(&current, &head);
		process_token(&token, &lasts, &current, &head);
		token = custom(NULL, " ", &lasts);
	}
	return (head);
}
