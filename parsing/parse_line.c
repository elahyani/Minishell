/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/17 19:13:01 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_sy_err(t_cmds *cmds)
{
	ft_putendl_fd("minishell: syntax error", 1);
	cmds->ret = 258;
	return (1);
}

void	parse_line(char **ln, t_cmds *cmds)
{
	int			i;
	int			j;
	t_cmd_list	*head;

	if (handle_stx_err(ln, cmds) || check_q(ln, cmds) || check_redir(ln, cmds))
		return ;
	i = -1;
	j = -1;
	head = NULL;
	cmds->quote = 0;
	cmds->ignore = 0;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*ln)[i]))
			cmds->quote = quote_activer((*ln)[i], cmds->quote);
		if (!cmds->quote && !cmds->ignore && (((*ln)[i] == ';') || !(*ln)[i + 1]) && j != -1)
		{
			if (head)
			{
				if (!(*ln)[i + 1] && (*ln)[i] != ';')
					add_front(&head, list_cmds(ft_substr(*ln, j + 1, i - j)));
				else
					add_front(&head, list_cmds(ft_substr(*ln, j + 1, i - j - 1)));
			}
			else
			{
				if (!(*ln)[i + 1] && (*ln)[i] != ';')
					head = list_cmds(ft_substr(*ln, j, i + 1));
				else
					head = list_cmds(ft_substr(*ln, j, i));
			}
			j = -1;
		}
		((*ln)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
		(j == -1) ? j = i : 0;
	}
	if (!head)
		head = list_cmds(ft_substr(*ln, j, i));
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
}
