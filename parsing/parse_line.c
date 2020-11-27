/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/27 14:00:04 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_sy_err()
{
	// t_cmd_list *tmp;
	
	puts("________________1");
	ft_putendl_fd("minishell: syntax error", 1);
	// if (cmds->cmd_list)
	// {
	// 	puts("________________2");
	// 	while (cmds->cmd_list)
	// 	{
	// 		puts("________________3");
	// 		tmp = cmds->cmd_list->next;
	// 		free(cmds->cmd_list);
	// 		cmds->cmd_list = tmp;
	// 	}
	// }
	return (1);
}

int		handle_syntax_err(char **line)
{
	int		quote;
	int		i;

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[0] == ';' || ((*line)[i] == ';' && (*line)[i + 1] == ';' && !(*line)[i + 2]))
		{
			return (get_sy_err());
		}
		else if ((*line)[0] == '|' || ((*line)[i] == '|' && (!(*line)[i + 1])))
		{
			return (get_sy_err());
		}
		else if ((*line)[i] == '\\' && !(*line)[i + 1])
		{
			return (get_sy_err());
		}
		else if (((*line)[i] == '>' && !(*line)[i + 1]) || ((*line)[i] == '<' && !(*line)[i + 1]))
		{
			return (get_sy_err());	
		}
		else if (ft_strchr("\"'", (*line)[i]))
		{
			if ((*line)[i - 1] != '\\')
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

/**
 * syntax err:
 * [-]____________	[;], [_;cmd], [cmd;;], [;cmd]
 * [-]____________	[|], [_|cmd], [cmd|], [|cmd]
 * [-]____________	[cmd|;], [cmd;|]
 * [-]____________	< , > , >>, cmd >, cmd <
 * [-]____________	", ', "cmd, 'cmd, cmd', cmd", \, cmd\
 * [-]____________	
*/
