/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/25 14:28:56 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	int		len;
	int		i;
	int		quote;

	quote = 0;
	i = -1;
	len = ft_strlen(*line);
	while ((*line)[++i])
	{
		if ((*line)[0] == ';' ||
		((*line)[i] == ';' && (*line)[i + 1] == ';' && !(*line)[i + 2]))
		{
			ft_putendl_fd("bash: syntax error near to unexpected token `;'", 1);
			return ;
		}
		else if ((*line)[0] == '|' || ((*line)[i] == '|' && !(*line)[i + 1]))
		{
			ft_putendl_fd("bash: syntax error near to unexpected token `|'", 1);
			return ;
		}
		else if ((*line)[i] == '\\' && !(*line)[i + 1])
		{
			ft_putendl_fd("bash: syntax error near to unexpected token `\\'", 1);
			return ;
		}
		else if (((*line)[i] == '>' && !(*line)[i + 1]) || 
		((*line)[i] == '<' && !(*line)[i + 1]))
		{
			ft_putendl_fd("bash: syntax error near to unexpected token `newline'", 1);
			return ;
		}
		else if (ft_strchr("\"'", (*line)[i]))
			quote++;
	}
	if (quote % 2 != 0)
	{
		ft_putendl_fd("bash: syntax error near to unexpected token `\"'", 1);
		return ;
	}
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
