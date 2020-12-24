/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:58:21 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 12:47:09 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		check_for_quote(t_cmds **cmds, char **ln, int *i)
{
	if ((*ln)[*i] == '\\' && (*cmds)->quote != 1)
		(*cmds)->ignore = (*cmds)->ignore ? 0 : 1;
	if (!(*cmds)->ignore && is_quote((*ln)[*i]))
		(*cmds)->quote = quote_activer((*ln)[*i], (*cmds)->quote);
}
