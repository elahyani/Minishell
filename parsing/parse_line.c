/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/21 14:25:48 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_sy_err(t_cmds *cmds)
{
	ft_putendl_fd("minishell: syntax error", 1);
	cmds->ret = 258;
	return (1);
}

void	ft_init(t_cmds **cmds, t_cmd_list **head, int *i, int *j)
{
	*i = -1;
	*j = -1;
	(*head) = NULL;
	(*cmds)->quote = 0;
	(*cmds)->ignore = 0;
}

void	semi_split(char **ln, t_cmd_list **head, int *i, int *j)
{
	if (*head)
	{
		if (!(*ln)[*i + 1] && (*ln)[*i] != ';')
			add_front(&(*head), list_cmds(ft_substr(*ln, *j + 1, *i - *j)));
		else
			add_front(&(*head),
			list_cmds(ft_substr(*ln, *j + 1, *i - *j - 1)));
	}
	else
	{
		if (!(*ln)[*i + 1] && (*ln)[*i] != ';')
			*head = list_cmds(ft_substr(*ln, *j, *i + 1));
		else
			*head = list_cmds(ft_substr(*ln, *j, *i));
	}
}

void	parse_line(char **ln, t_cmds *cmds)
{
	int			i;
	int			j;
	t_cmd_list	*head;

	if (handle_stx_err(ln, cmds) || check_q(ln, cmds) || check_redir(ln, cmds))
		return ;
	ft_init(&cmds, &head, &i, &j);
	while ((*ln)[++i])
	{
		check_for_quote(&cmds, ln, &i);
		if (!cmds->quote && !cmds->ignore && (((*ln)[i] == ';')
		|| !(*ln)[i + 1]) && j != -1)
		{
			semi_split(ln, &head, &i, &j);
			j = -1;
		}
		((*ln)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
		(j == -1) ? j = i : 0;
	}
	if (!head)
		head = list_cmds(ft_substr(*ln, j, i));
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
}
