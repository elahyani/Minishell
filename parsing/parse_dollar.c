/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:24 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 12:47:30 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_dollar_init(t_cmds **cmds, int *i, int *l, int *is_in_dq)
{
	*i = -1;
	*l = 0;
	*is_in_dq = 0;
	(*cmds)->tmp_d = NULL;
	(*cmds)->tmp1_d = NULL;
	(*cmds)->quote = 0;
	(*cmds)->ignore = 0;
	(*cmds)->arg_d = ft_strdup("");
}

char	*parse_dollar(t_cmds *cmds, char **line_list)
{
	int			i;
	int			l;
	int			is_in_dq;

	parse_dollar_init(&cmds, &i, &l, &is_in_dq);
	while ((*line_list)[++i])
	{
		manag_quotes_d(line_list, &cmds, &i, &is_in_dq);
		if ((*line_list)[i] == '$' && !cmds->ignore && !cmds->quote)
			set_env_val(line_list, &cmds, &i, &l);
		else
		{
			cmds->tmp2_d[0] = (*line_list)[i];
			cmds->tmp2_d[1] = '\0';
			cmds->tmp1_d = ft_strjoin(cmds->arg_d, cmds->tmp2_d);
			cmds->arg_d = ft_free_str(cmds->arg_d);
			cmds->arg_d = cmds->tmp1_d;
		}
		((*line_list)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	return (cmds->arg_d);
}
