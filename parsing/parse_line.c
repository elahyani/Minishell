/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/25 10:11:12 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(*line);
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
