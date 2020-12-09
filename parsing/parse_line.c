/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/09 14:46:36 by elahyani         ###   ########.fr       */
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

int		check_cmd(char *cmd, char *filename)
{
	int		i;

	i = -1;
	if (cmd)
	{
		while ((cmd)[++i])
			if (ft_isalpha((cmd)[i]))
				return (0);
	}
	else if (filename)
	{
		while ((filename)[++i])
			if (ft_isprint((filename)[i]))
				return (0);
	}
	return (1);
}

int		check_q(char **ln, t_cmds *cmds)
{
	int		i;

	i = -1;
	cmds->ignore = 0;
	cmds->quote = 0;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (((!cmds->quote || (cmds->quote && is_quote((*ln)[i]) == cmds->quote)) && is_quote((*ln)[i]) && !cmds->ignore))
			cmds->quote = quote_activer((*ln)[i], cmds->quote);
		if ((*ln)[i] != '\\' && cmds->ignore)
			cmds->ignore = 0;
	}
	if (cmds->ignore || cmds->quote)
		return (get_sy_err());
	return (0);
}

int		check_redir(char **ln, t_cmds *cmds)
{
	int		i;

	i = -1;
	cmds->quote = 0;
	cmds->ignore = 0;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*ln)[i]))
			cmds->quote = quote_activer((*ln)[i], cmds->quote);
		if (((*ln)[i] == '>' || (*ln)[i] == '<') && !cmds->ignore && !cmds->quote)
		{
			if (check_cmd(NULL, *ln + i + 1))
				return (get_sy_err());
			else if (((*ln)[i] == '>' && (*ln)[i + 1] == '>' &&
			(*ln)[i + 2] == '>') || ((*ln)[i] == '<' && (*ln)[i + 1] == '<'))
				return (get_sy_err());
		}
		if ((*ln)[i] != '\\' && cmds->ignore)
			cmds->ignore = 0;
	}
	return (0);
}

int		handle_stx_err(char **ln, t_cmds *cmds)
{
	int		i;
	int		j;
	char	*iscmd;

	j = -1;
	i = -1;
	cmds->quote = 0;
	cmds->ignore = 0;
	iscmd = NULL;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote((*ln)[i]))
			cmds->quote = quote_activer((*ln)[i], cmds->quote);
		if (((*ln)[i] == ';' || (*ln)[i] == '|') && !cmds->ignore && !cmds->quote)
		{
			iscmd = ft_substr(*ln, j, i - j);
			j = -1;
			if ((*ln)[i] == '|' && !(*ln)[i + 1])
				return (get_sy_err());
			else if (check_cmd(iscmd, NULL))
				return (get_sy_err());
		}
		else if ((*ln)[i] == '\\' && !(*ln)[i + 1] && ((i && (*ln)[i - 1] != '\\') || !i))
			return (get_sy_err());
		(j == -1) ? j = i : 0;
		if ((*ln)[i] != '\\' && cmds->ignore)
			cmds->ignore = 0;
	}
	return (0);
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
		if (!cmds->quote && !cmds->ignore && (((*ln)[i] == ';' && (*ln)[i - 1] != '\\') || !(*ln)[i + 1]))
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
