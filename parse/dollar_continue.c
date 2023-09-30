/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:36:53 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:25:25 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_slash_impact(int is_escaped, char quote_char)
{
	if (!is_escaped && quote_char == '"')
		quote_char = '\0';
	else if (!is_escaped)
		quote_char = '"';
	return (quote_char);
}

char	ft_pedro(char quote_char)
{
	if (quote_char == '\'')
		quote_char = '\0';
	else
		quote_char = '\'';
	return (quote_char);
}

size_t	ft_get_env_replace(char *input, t_cmd *ubuntu, size_t required_length,
		size_t i_res)
{
	char	var_name[256];
	char	*var_value;
	size_t	var_start;

	ubuntu->i++;
	var_start = 0;
	while (input[ubuntu->i] && (my_isalnum(input[ubuntu->i])
			|| input[ubuntu->i] == '_'))
		var_name[var_start++] = input[ubuntu->i++];
	var_name[var_start] = '\0';
	var_value = getenv(var_name);
	if (var_value)
	{
		strncpy(&ubuntu->res[i_res], var_value, required_length - i_res);
		i_res += strlen(var_value);
	}
	return (i_res);
}

char	*replace_env_vars(char *ip)
{
	t_cmd	b;

	b.required_length = calculate_required_length(ip);
	b.i_resu = 0;
	b.res = malloc(b.required_length + 1);
	b.q_c = '\0';
	b.is_escaped = 0;
	b.i = 0;
	while (ip[b.i])
	{
		if (ip[b.i] == '\\' && b.q_c == '"' && (ip[b.i + 1] == '"' || ip[b.i
					+ 1] == '\\' || ip[b.i + 1] == '$'))
			handle_back_slash(&b, ip);
		else if (ip[b.i] == '"' && b.q_c != '\'')
			handle_double_quote(&b);
		else if (ip[b.i] == '\'' && b.q_c != '"')
			handle_single_quote(&b);
		else if (ip[b.i] == '$' && b.q_c != '\'')
			handle_dollar_sign(&b, ip);
		else if (ip[b.i] != '\\')
			handle_other_cases(&b, ip);
	}
	b.res[b.i_resu] = '\0';
	return (b.res);
}

// void	var_loop(void);
// char	*replace_env_vars(char *ip)
// {
// 	t_cmd b;
// 	size_t required_length;
// 	char q_c;
// 	int is_escaped;
// 	size_t i_resu = 0;

// 	required_length = calculate_required_length(ip);
// 	b.res = malloc(required_length + 1);
// 	if (!b.res)
// 		exit(1);
// 	q_c = '\0';
// 	is_escaped = 0;
// 	b.i = 0;
// 	while (ip[b.i])
// 	{
// 		if (ip[b.i] == '\\' && q_c == '"' &&
// 			(ip[b.i + 1] == '"' || ip[b.i + 1] == '\\'|| ip[b.i + 1] == '$'))
// 		{
// 			b.res[i_resu++] = ip[b.i + 1];
// 			b.i += 2;
// 		}
// 		if (ip[b.i] == '"' && q_c != '\'')
// 		{
// 			q_c = ft_slash_impact(is_escaped, q_c);
// 			b.i++;
// 			continue ;
// 		}
// 		if (ip[b.i] == '\'' && q_c != '"')
// 		{
// 			q_c = ft_pedro(q_c);
// 			b.i++;
// 			continue ;
// 		}
// 		if (ip[b.i] == '$' && q_c != '\'')
// 		{
// 			i_resu = ft_get_env_replace(ip, &b, required_length,
// 					i_resu);
// 			continue ;
// 		}
// 		if (ip[b.i] != '\\')
// 		is_escaped = 0;
// 			b.res[i_resu++] = ip[b.i++];
// 	}
// 	b.res[i_resu] = '\0';
// 	return (b.res);
// }
