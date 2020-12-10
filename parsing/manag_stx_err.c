/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_stx_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:10:55 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/10 14:06:04 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_cmd(char *cmd)
{
	int		i;

	i = -1;
	if (cmd)
	{
		while (cmd[++i])
			if ((cmd[i] != ';' && cmd[i] != '|') && ft_isprint((cmd)[i]))
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
		if (((!cmds->quote || (cmds->quote &&
		is_quote((*ln)[i]) == cmds->quote)) &&
		is_quote((*ln)[i]) && !cmds->ignore))
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
		if (((*ln)[i] == '>' || (*ln)[i] == '<') &&
		!cmds->ignore && !cmds->quote)
		{
			if (check_cmd(*ln + i + 1))
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

int		semi_pipe_stx_err(char **ln, t_cmds *cmds)
{
	char	*iscmd;
	int		i;
	int		j;

	i = -1;
	j = -1;
	iscmd = NULL;
	while ((*ln)[++i])
	{
		if (((*ln)[i] == ';' || (*ln)[i] == '|') &&
		!cmds->ignore && !cmds->quote)
		{
			iscmd = ft_substr(*ln, j, i - j);
			j = -1;
			if ((*ln)[i] == '|' && !(*ln)[i + 1])
				return (get_sy_err());
			else if (check_cmd(iscmd))
				return (get_sy_err());
		}
		(j == -1) ? j = i : 0;
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
		if (((*ln)[i] == ';' || (*ln)[i] == '|') &&
		!cmds->ignore && !cmds->quote)
			return (semi_pipe_stx_err(ln, cmds));
		else if ((*ln)[i] == '\\' && !(*ln)[i + 1] &&
		((i && (*ln)[i - 1] != '\\') || !i))
			return (get_sy_err());
		((*ln)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	return (0);
}
