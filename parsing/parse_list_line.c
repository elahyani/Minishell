/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/17 19:42:56 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(char **line, t_cmd_list **hd, int *i, int *j, t_cmds *cmds)
{
	if (!(*hd)->prev || ((*hd)->prev && (*hd)->prev->end))
		(*hd)->start = 1;
	(*hd)->data = ft_substr(*line, *j, *i - *j);
	(*hd)->p = 1;
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	add_front(&(*hd), list_line_cmds(NULL));
}

void	parse_redir(char **line, t_cmd_list **hd, int *j, int *i, t_cmds *cmds)
{
	if ((*line)[*i] == '<')
		(*hd)->redir = '<';
	else if ((*line)[*i] == '>')
	{
		if ((*line)[*i + 1] == '>')
		{
			(*hd)->redir = 'a';
			(*i)++;
		}
		else
			(*hd)->redir = '>';
	}
	(*hd)->data = ft_substr(*line, *j, *i - *j - 1);
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	add_front(&(*hd), list_line_cmds(NULL));
}

void	loop_line(char **line, t_cmd_list **hd, int *i, int *j, t_cmds *cmds)
{
	while ((*line)[++(*i)])
	{
		if ((*line)[*i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*line)[*i]))
			cmds->quote = quote_activer((*line)[*i], cmds->quote);
		if ((*line)[*i + 1] == '\0' && ((*hd)->end = 1) &&
		!cmds->ignore && !cmds->quote)
		{
			if (((*hd)->prev && (*hd)->prev->end) || !(*hd)->prev)
				(*hd)->start = 1;
			(*hd)->data = ft_substr(*line, *j, *i - *j + 1);
		}
		else if ((*line)[*i] == '|' && (*line)[*i - 1] != '\\' &&
		!cmds->ignore && !cmds->quote)
		{
			parse_pipe(line, &(*hd), i, j, cmds);
			*j = *i + 1;
		}
		else if (((*line)[*i] == '<' || (*line)[*i] == '>') &&
		!cmds->ignore && !cmds->quote)
		{
			parse_redir(line, &(*hd), j, i, cmds);
			*j = *i + 1;
		}
		((*line)[*i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
}

void	parse_list_line(char **line, t_cmd_list *list, t_cmds *cmds)
{
	int			i;
	int			j;
	char		*tmp;
	t_cmd_list	*hd;

	j = 0;
	i = -1;
	hd = list;
	tmp = NULL;
	hd->data = NULL;
	cmds->quote = 0;
	cmds->ignore = 0;
	if (ft_strchr(*line, '$'))
	{
		tmp = parse_dollar(cmds, line);
		ft_free_str(line);
		*line = tmp;
	}
	loop_line(line, &hd, &i, &j, cmds);
	// while ((*line)[++i])
	// {
	// 	if ((*line)[i] == '\\' && cmds->quote != 1)
	// 		cmds->ignore = cmds->ignore ? 0 : 1;
	// 	if (!cmds->ignore && is_quote((*line)[i]))
	// 		cmds->quote = quote_activer((*line)[i], cmds->quote);
	// 	if ((*line)[i + 1] == '\0' && (hd->end = 1) &&
	// 	!cmds->ignore && !cmds->quote)
	// 	{
	// 		((hd->prev && hd->prev->end) || !hd->prev) ? hd->start = 1 : 0;
	// 		hd->data = ft_substr(*line, j, i - j + 1);
	// 	}
	// 	else if ((*line)[i] == '|' && (*line)[i - 1] != '\\' && !cmds->ignore && !cmds->quote)
	// 	{
	// 		parse_pipe(line, &hd, &i, &j, cmds);
	// 		j = i + 1;
	// 	}
	// 	else if (((*line)[i] == '<' || (*line)[i] == '>') && !cmds->ignore && !cmds->quote)
	// 	{
	// 		parse_redir(line, &hd, &j, &i, cmds);
	// 		j = i + 1;
	// 	}
	// 	((*line)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	// }
	if (!hd->data)
	{
		((hd->prev && hd->prev->end) || !hd->prev) ? hd->start = 1 : 0;
		hd->data = ft_substr(*line, j, i - j);
	}
	hd->args = split_cmd(hd->data, ' ', cmds);
	list = hd;
}
