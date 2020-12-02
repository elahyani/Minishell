/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/02 11:42:40 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_list_line(char **line, t_cmd_list *list, t_cmds *cmds)
{	
	t_cmd_list	*hd;
	int			len;
	int			i;

	parse_dollar(cmds, line);
	len = ft_strlen(*line);
	hd = list_line_cmds(list, *line, 1);
	i = -1;
	while (++i <= len)
	{
		if ((*line)[i] == ';' || (*line)[i] == '\0')
		{
			((hd->prev && hd->prev->end) || !hd->prev) ? hd->start = 1 : 0;
			hd->end = 1;
			if ((*line)[i] == ';')
				break ;
		}
		else if ((*line)[i] == '|' && (*line)[i - 1] != '\\')
		{
			(!hd->prev || (hd->prev && hd->prev->end)) ? hd->start = 1 : 0;
			(*line)[i] = '\0';
			if (hd->next)
			{
				update_list(&hd, &hd->next, list_line_cmds(NULL, *line + i + 1, 1));
				hd = hd->next;
			}
			else
				add_front(&hd, list_line_cmds(NULL, *line + i + 1, 1));
		}
		else if ((*line)[i] == '<')
			hd->redir = '<';
		else if ((*line)[i] == '>')
		{
			if ((*line)[i + 1] == '>' && (i++))
				hd->redir = 'a';
			else
				hd->redir = '>';
		}
	}
}