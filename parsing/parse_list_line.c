/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/14 14:23:55 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(char **line, t_cmd_list **hd, int *i, t_cmds *cmds)
{
	(!(*hd)->prev || ((*hd)->prev && (*hd)->prev->end)) ? (*hd)->start = 1 : 0;
	(*line)[*i] = '\0';
	// (*hd)->num
	(*hd)->p = 1;
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	if ((*hd)->next)
	{
		update_list(hd, &(*hd)->next, list_line_cmds(NULL, *line + *i + 1, 1));
		(*hd) = (*hd)->next;
	}
	else
		add_front(hd, list_line_cmds(NULL, *line + *i + 1, 1));
}

void	parse_redir(char **line, t_cmd_list **hd, int *i, t_cmds *cmds)
{
	if ((*line)[*i] == '<')
		(*hd)->redir = '<';
	else if ((*line)[*i] == '>')
	{
		if ((*line)[*i + 1] == '>')
		{
			(*hd)->redir = 'a';
			(*line)[*i] = '\0';
			(*i)++;
		}
		else
			(*hd)->redir = '>';
	}
	(*line)[*i] = '\0';
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	if ((*hd)->next)
	{
		update_list(hd, &(*hd)->next, list_line_cmds(NULL, *line + *i + 1, 1));
		(*hd) = (*hd)->next;
	}
	else
		add_front(hd, list_line_cmds(NULL, *line + *i + 1, 1));
}

void	parse_list_line(char **line, t_cmd_list *list, t_cmds *cmds)
{
	t_cmd_list	*hd;
	int			len;
	int			i;

	cmds->num_pipe = 0;
	parse_dollar(cmds, line);
	len = ft_strlen(*line);
	hd = list_line_cmds(list, *line, 1);
	i = -1;
	cmds->quote = 0;
	cmds->ignore = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*line)[i]))
			cmds->quote = quote_activer((*line)[i], cmds->quote);
		if (((*line)[i] == ';' || (*line)[i + 1] == '\0') && (hd->end = 1) &&
		!cmds->ignore && !cmds->quote)
		{
			((hd->prev && hd->prev->end) || !hd->prev) ? hd->start = 1 : 0;
			hd->args = split_cmd(hd->data, ' ', cmds);
			if ((*line)[i] == ';')
				break ;
		}
		else if ((*line)[i] == '|' && (*line)[i - 1] != '\\' && !cmds->ignore && !cmds->quote)
			parse_pipe(line, &hd, &i, cmds);
		else if (((*line)[i] == '<' || (*line)[i] == '>') && !cmds->ignore && !cmds->quote)
			parse_redir(line, &hd, &i, cmds);
		if ((*line)[i] != '\\' && cmds->ignore)
			cmds->ignore = 0;
	}
	hd->args = split_cmd(hd->data, ' ', cmds);
}
