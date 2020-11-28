/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/27 11:40:32 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmds(t_cmds *cmds)
{
	t_cmd_list *tmp;

	if (cmds->cmd_list)
		while (cmds->cmd_list)
		{
			tmp = cmds->cmd_list;
			cmds->cmd_list = cmds->cmd_list->next;
			free(tmp);
		}
}

int		handle_syntax_err(t_cmds *cmds, char **line)
{
	int		quote;
	int		i;

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[0] == ';' ||
		((*line)[i] == ';' && (*line)[i + 1] == ';' && !(*line)[i + 2]))
		{
			ft_putendl_fd("minishell: syntax error near to unexpected token `;'", 1);
			free_cmds(cmds);
			return (1);
		}
		else if ((*line)[0] == '|' || ((*line)[i] == '|' && ((!(*line)[i + 1]) || (*line)[i + 1] == ' ')))
		{
			ft_putendl_fd("minishell: syntax error near to unexpected token `|'", 1);
			free_cmds(cmds);
			return (1);
		}
		else if ((*line)[i] == '\\' && !(*line)[i + 1])
		{
			ft_putendl_fd("minishell: syntax error near to unexpected token `\\'", 1);
			free_cmds(cmds);
			return (1);
		}
		else if (((*line)[i] == '>' && !(*line)[i + 1]) || 
		((*line)[i] == '<' && !(*line)[i + 1]))
		{
			ft_putendl_fd("minishell: syntax error near to unexpected token `newline'", 1);
			free_cmds(cmds);
			return (1);
		}
		else if (ft_strchr("\"'", (*line)[i]))
			if ((*line)[i - 1] != '\\')
				quote++;
	}
	if (quote % 2 != 0)
	{
		ft_putendl_fd("minishell: syntax error near to unexpected token `\"'", 1);
		free_cmds(cmds);
		return (1);
	}
	return (0);
}

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	int		len;
	int		i;
	int		err;

	if ((err = handle_syntax_err(cmds, line)))
		return ;
	len = ft_strlen(*line);
	i = -1;
	head = list_cmds(NULL, *line, 0);
	while (++i <= len)
	{
		if ((*line)[i] == ';' || (*line)[i] == '\0')
		{
			if ((*line)[i] == ';')
			{
				(*line)[i] = '\0';
				add_front(&head, list_cmds(NULL, *line + i + 1, 0));
			}
		}
	}
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
}
// echo "hi ""jj"" po"