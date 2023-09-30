/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_continue_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:06:48 by bel-kase          #+#    #+#             */
/*   Updated: 2023/09/29 23:25:21 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_back_slash(t_cmd *b, char *ip)
{
	b->res[b->i_resu++] = ip[b->i + 1];
	b->i += 2;
}

void	handle_double_quote(t_cmd *b)
{
	b->q_c = ft_slash_impact(b->is_escaped, b->q_c);
	b->i++;
}

void	handle_single_quote(t_cmd *b)
{
	b->q_c = ft_pedro(b->q_c);
	b->i++;
}

void	handle_dollar_sign(t_cmd *b, char *ip)
{
	b->i_resu = ft_get_env_replace(ip, b, b->required_length, b->i_resu);
}

void	handle_other_cases(t_cmd *b, char *ip)
{
	b->is_escaped = 0;
	b->res[b->i_resu++] = ip[b->i++];
}
