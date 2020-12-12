/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/12 19:22:24 by ichejra          ###   ########.fr       */
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
	int			len;
	int			i;
	t_cmd_list	*head;

	if (handle_stx_err(ln, cmds) || check_q(ln, cmds) || check_redir(ln, cmds))
		return ;
	len = ft_strlen(*ln);
	i = -1;
	head = list_cmds(NULL, *ln, 0);
	cmds->quote = 0;
	cmds->ignore = 0;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*ln)[i]))
			cmds->quote = quote_activer((*ln)[i], cmds->quote);
		if (!cmds->quote && !cmds->ignore && (((*ln)[i] == ';' &&
		(*ln)[i - 1] != '\\') || !(*ln)[i + 1]))
		{
			if ((*ln)[i] == ';')
			{
				(*ln)[i] = '\0';
				add_front(&head, list_cmds(NULL, *ln + i + 1, 0));
			}
		}
		if ((*ln)[i] != '\\' && cmds->ignore)
			cmds->ignore = 0;
	}
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
}
