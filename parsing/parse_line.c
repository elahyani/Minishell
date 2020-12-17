/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/17 10:37:38 by elahyani         ###   ########.fr       */
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

void	parse_line(char **ln, t_cmds *cmds)
{
	int			i;
	int			j;
	t_cmd_list	*head;

	if (handle_stx_err(ln, cmds) || check_q(ln, cmds) || check_redir(ln, cmds))
		return ;
	i = -1;
	j = -1;
	head = NULL;
	cmds->quote = 0;
	cmds->ignore = 0;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*ln)[i]))
			cmds->quote = quote_activer((*ln)[i], cmds->quote);
		if (!cmds->quote && !cmds->ignore && (((*ln)[i] == ';') || !(*ln)[i + 1]) && j != -1)
		{
			if (head)
			{
				if (!(*ln)[i + 1] && (*ln)[i] != ';')
					add_front(&head, list_cmds(NULL, ft_substr(*ln, j + 1, i - j), 0));
				else
					add_front(&head, list_cmds(NULL, ft_substr(*ln, j + 1, i - j - 1), 0));
			}
			else
			{
				if (!(*ln)[i + 1] && (*ln)[i] != ';')
					head = list_cmds(NULL, ft_substr(*ln, j, i + 1), 0);
				else
					head = list_cmds(NULL, ft_substr(*ln, j, i), 0);
			}
			j = -1;
		}
		((*ln)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
		(j == -1) ? j = i : 0;
	}
	if (!head)
		head = list_cmds(NULL, ft_substr(*ln, j, i), 0);
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
	//(*ln) ? ft_free_str(ln) : 0;
}
