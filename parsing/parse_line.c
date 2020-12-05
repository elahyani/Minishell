/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:28 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/05 10:26:41 by elahyani         ###   ########.fr       */
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

int		check_q_err(char **ln)
{
	int		i;
	int		quote;
	int		q;

	i = -1;
	quote = 0;
	q = 0;
	while ((*ln)[++i])
		if (((*ln)[i] == '\"' || (*ln)[i] == '\'') && (q = (*ln)[i]))
			break ;
	i = -1;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '\"' && q == '\"')
			((i && (*ln)[i - 1] != '\\') || !i) ? quote++ : 0;
		else if ((*ln)[i] == '\'' && q == '\'')
			((i && (*ln)[i - 1] != '\\') || !i) ? quote++ : 0;
		else if ((*ln)[i] == '\"' && quote % 2 == 0)
			return (get_sy_err());
		else if ((*ln)[i] == '\'' && quote % 2 == 0)
			return (get_sy_err());
	}
	if (quote % 2 != 0)
		return (get_sy_err());
	return (0);
}

int		check_redir(char **ln)
{
	int		i;

	i = -1;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == '>' || (*ln)[i] == '<')
		{
			if (check_cmd(NULL, *ln + i + 1))
				return (get_sy_err());
			else if (((*ln)[i] == '>' && (*ln)[i + 1] == '>' &&
			(*ln)[i + 2] == '>') || ((*ln)[i] == '<' && (*ln)[i + 1] == '<'))
				return (get_sy_err());
		}
	}
	return (0);
}

int		handle_syntax_err(char **ln)
{
	int		i;
	int		j;
	char	*iscmd;

	j = -1;
	i = -1;
	iscmd = NULL;
	while ((*ln)[++i])
	{
		if ((*ln)[i] == ';' || (*ln)[i] == '|')
		{
			iscmd = ft_substr(*ln, j, i - j);
			j = -1;
			if ((*ln)[i] == '|' && !(*ln)[i + 1])
				return (get_sy_err());
			else if (check_cmd(iscmd, NULL))
				return (get_sy_err());
		}
		else if ((*ln)[i] == '\\' && !(*ln)[i + 1] && (*ln)[i - 1] != '\\')
			return (get_sy_err());
		(j == -1l) ? j = i : 0;
	}
	return (0);
}

void	parse_line(char **line, t_cmds *cmds)
{
	int			len;
	int			i;
	t_cmd_list	*head;

	if (handle_syntax_err(line) || check_q_err(line) || check_redir(line))
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
