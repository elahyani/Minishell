/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/01 14:37:06 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_list_line(char **line_list, t_cmd_list *list, t_cmds *cmds)
{	
	t_cmd_list	*head;
	int			len;
	int			i;

	parse_dollar(cmds, line_list);
	len = ft_strlen(*line_list);
	head = list_line_cmds(list, *line_list, 1);
	i = -1;
	while (++i <= len)
	{
		if ((*line_list)[i] == ';' || (*line_list)[i] == '\0')
		{
			if ((head->prev && head->prev->end) || !head->prev)
				head->start = 1;
			if (head->prev && !head->start)
				head->end = 1;
			head->end = 1;
			if ((*line_list)[i] == ';')
				break ;
		}
		else if ((*line_list)[i] == '|' && (*line_list)[i - 1] != '\\')
		{
			if (!head->prev || (head->prev && head->prev->end))
				head->start = 1;
			(*line_list)[i] = '\0';
			if (head->next)
			{
				update_list(&head, &head->next, list_line_cmds(NULL, *line_list + i + 1, 1));
				head = head->next;
			}
			else
				add_front(&head, list_line_cmds(NULL, *line_list + i + 1, 1));
		}
		else if ((*line_list)[i] == '<')
			head->redir = '<';
		else if ((*line_list)[i] == '>')
		{
			if ((*line_list)[i + 1] == '>')
			{
				head->redir = 'a';
				i++;
			}
			else
				head->redir = '>';
		}
	}
}