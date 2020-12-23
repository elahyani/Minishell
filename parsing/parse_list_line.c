/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/23 11:34:47 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(char **line, t_cmd_list **hd, t_cmds *cmds, t_inc **inc)
{
	if (!(*hd)->prev || ((*hd)->prev && (*hd)->prev->end))
		(*hd)->start = 1;
	(*hd)->data = ft_substr(*line, (*inc)->j, (*inc)->i - (*inc)->j);
	(*hd)->p = 1;
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	add_front(&(*hd), list_line_cmds(NULL));
}

void	parse_redir(char **line, t_cmd_list **hd, t_cmds *cmds)
{
	if ((*line)[cmds->inc->i] == '<')
		(*hd)->redir = '<';
	else if ((*line)[cmds->inc->i] == '>')
	{
		if ((*line)[cmds->inc->i + 1] == '>')
		{
			(*hd)->redir = 'a';
			(cmds->inc->i)++;
		}
		else
			(*hd)->redir = '>';
	}
	(*hd)->data = ft_substr(*line, cmds->inc->j, cmds->inc->i -
	cmds->inc->j - 1);
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	add_front(&(*hd), list_line_cmds(NULL));
}

void	loop_line(char **line, t_cmd_list **hd, t_cmds *cmds, t_inc **ic)
{
	while ((*line)[++((*ic)->i)])
	{
		check_for_quote(&cmds, line, &(*ic)->i);
		if ((*line)[(*ic)->i + 1] == '\0' && ((*hd)->end = 1) &&
		!cmds->ignore && !cmds->quote)
		{
			if (((*hd)->prev && (*hd)->prev->end) || !(*hd)->prev)
				(*hd)->start = 1;
			(*hd)->data = ft_substr(*line, (*ic)->j, (*ic)->i - (*ic)->j + 1);
		}
		else if ((*line)[(*ic)->i] == '|' && (*line)[(*ic)->i - 1] != '\\' &&
		!cmds->ignore && !cmds->quote)
		{
			parse_pipe(line, &(*hd), cmds, ic);
			(*ic)->j = (*ic)->i + 1;
		}
		else if (((*line)[(*ic)->i] == '<' || (*line)[(*ic)->i] == '>') &&
		!cmds->ignore && !cmds->quote)
		{
			parse_redir(line, &(*hd), cmds);
			(*ic)->j = (*ic)->i + 1;
		}
		((*line)[(*ic)->i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
}

void	parse_list_line(char **line, t_cmd_list *list, t_cmds *cmds)
{
	char		*tmp;
	t_cmd_list	*hd;

	cmds->inc = malloc(sizeof(t_inc *));
	cmds->inc->j = 0;
	cmds->inc->i = -1;
	hd = list;
	tmp = NULL;
	if (ft_strchr(*line, '$'))
	{
		tmp = parse_dollar(cmds, line);
		*line = ft_free_str(*line);
		*line = tmp;
	}
	loop_line(line, &hd, cmds, &cmds->inc);
	if (!hd->data)
	{
		((hd->prev && hd->prev->end) || !hd->prev) ? hd->start = 1 : 0;
		hd->data = ft_substr(*line, cmds->inc->j, cmds->inc->i - cmds->inc->j);
	}
	hd->args = split_cmd(hd->data, ' ', cmds);
	free(cmds->inc);
	list = hd;
}
