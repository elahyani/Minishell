/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:31 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/22 12:57:10 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			parse_pipe(char **line, t_cmd_list **hd, t_cmds *cmds)
{
	if (!(*hd)->prev || ((*hd)->prev && (*hd)->prev->end))
		(*hd)->start = 1;
	(*hd)->data = ft_substr(*line, cmds->j, cmds->i - cmds->j);
	(*hd)->p = 1;
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	add_front(&(*hd), list_line_cmds(NULL));
}

void			parse_redir(char **line, t_cmd_list **hd, t_cmds *cmds)
{
	if ((*line)[cmds->i] == '<')
		(*hd)->redir = '<';
	else if ((*line)[cmds->i] == '>')
	{
		if ((*line)[cmds->i + 1] == '>')
		{
			(*hd)->redir = 'a';
			(cmds->i)++;
		}
		else
			(*hd)->redir = '>';
	}
	(*hd)->data = ft_substr(*line, cmds->j, cmds->i - cmds->j - 1);
	(*hd)->args = split_cmd((*hd)->data, ' ', cmds);
	add_front(&(*hd), list_line_cmds(NULL));
}

void			loop_line(char **line, t_cmd_list **hd, t_cmds *cmds)
{
	cmds->j = 0;
	cmds->i = -1;
	puts(*line);
	while ((*line)[++cmds->i])
	{
		check_for_quote(&cmds, line, &cmds->i);
		if ((*line)[cmds->i + 1] == '\0' && ((*hd)->end = 1) &&
		!cmds->ignore && !cmds->quote)
		{
			puts("===> END \\0 ");
			printf("Before : i=|%d|\n", cmds->i);
			if (((*hd)->prev && (*hd)->prev->end) || !(*hd)->prev)
				(*hd)->start = 1;
			(*hd)->data = ft_substr(*line, cmds->j, cmds->i - cmds->j + 1);
			printf("After : i=|%d|\n", cmds->i);
			sleep(1);
		}
		else if ((*line)[cmds->i] == '|' && (*line)[cmds->i - 1] != '\\' &&
		!cmds->ignore && !cmds->quote)
		{
			puts("===> PIPE ");
			printf("Before : i=|%d|\n", cmds->i);
			parse_pipe(line, &(*hd), cmds);
			cmds->j = cmds->i + 1;
			printf("After : i=|%d|\n", cmds->i);
			sleep(1);
		}
		else if (((*line)[cmds->i] == '<' || (*line)[cmds->i] == '>') &&
		!cmds->ignore && !cmds->quote)
		{
			parse_redir(line, &(*hd), cmds);
			cmds->j = cmds->i + 1;
		}
		cmds->ignore = ((*line)[cmds->i] != '\\' && cmds->ignore) ?  0 : cmds->ignore;
	}
}

// echo hello$PWD ; echo $PWD | echo "$"PWD | echo $"PWD" ; echo "$PWD" ; echo '$PWD' | echo '$'PWD | echo " "$PWD" " ; echo '" '$PWD' "' ; echo \$\$\$\$ ; echo \anychar\anychar\anychar ; echo \'\'\'\' ;  echo \"\"\" | echo \\"$PWD"

void			parse_list_line(char **line, t_cmd_list *list, t_cmds *cmds)
{
	char		*tmp;
	t_cmd_list	*hd;

	hd = list;
	tmp = NULL;
	cmds->quote = 0;
	cmds->ignore = 0;
	if (ft_strchr(*line, '$'))
	{
		tmp = parse_dollar(cmds, line);
		ft_free_str(*line);
		*line = tmp;
	}
	loop_line(line, &hd, cmds);
	if (!hd->data)
	{
		((hd->prev && hd->prev->end) || !hd->prev) ? hd->start = 1 : 0;
		hd->data = ft_substr(*line, cmds->j, cmds->i - cmds->j);
	}
	hd->args = split_cmd(hd->data, ' ', cmds);
	list = hd;
}
 echo /Users/elahyani/Desktop/Minishell | echo "$"PWD | echo "PWD"