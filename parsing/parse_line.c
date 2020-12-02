/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/02 14:16:30 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_sy_err()
{
	// t_cmd_list *tmp;
	
	//puts("________________1");
	ft_putendl_fd("minishell: syntax error", 1);
	// if (cmds->cmd_list)
	// {
	// 	puts("________________2");
	// 	while (cmds->cmd_list)b
	// 	{
	// 		puts("________________3");
	// 		tmp = cmds->cmd_list->next;
	// 		free(cmds->cmd_list);
	// 		cmds->cmd_list = tmp;
	// 	}
	// }
	return (1);
}

int		handle_syntax_err(char **ln)
{
	int		quote;
	int		i;
	int		dq;
	int		skip;

	skip = 1;
	dq = 0;
	quote = 0;
	i = -1;
	while ((*ln)[++i])
	{
		if ((*ln)[0] == ';' || ((*ln)[i] == ';' && (*ln)[i + 1] == ';' && !(*ln)[i + 2]))
		{
			return (get_sy_err());
		}
		else if ((*ln)[0] == '|' || ((*ln)[i] == '|' && (!(*ln)[i + 1])))
		{
			return (get_sy_err());
		}
		else if ((*ln)[i] == '\\' && (/* !(*ln)[i + 1] || */ (*ln)[i + 1] != '\\') && skip == 0)
		{
			skip = 1;
			return (get_sy_err());
		}
		else if (((*ln)[i] == '>' && !(*ln)[i + 1]) || ((*ln)[i] == '<' && !(*ln)[i + 1]))
		{
			return (get_sy_err());	
		}
		else if ((*ln)[i] == '\"')
		{
			dq++;
			if (dq % 2 == 0)
				dq = 0;
			if ((i && (*ln)[i - 1] != '\\') || !i)
				quote++;
		}
		else if ((*ln)[i] == '\'')
		{
			if ((i && (*ln)[i - 1] != '\\') || !i)
				if (!dq)
					quote++;
		}
	}
	if (quote % 2 != 0)
		return (get_sy_err());
	return (0);
}

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	int		len;
	int		i;
	int		err;

	if ((err = handle_syntax_err(line)))
		return ;
	len = ft_strlen(*line);
	i = -1;
	head = list_cmds(NULL, *line, 0);
	while (++i <= len)
	{
		if (((*line)[i] == ';' && (*line)[i - 1] != '\\') || (*line)[i] == '\0')
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
