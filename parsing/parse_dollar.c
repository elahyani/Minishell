/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:24 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/13 14:17:33 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int		get_exit_status(t_cmds *cmds)
// {
// 	if (cmds->exit_status == 127)
// 		puts("command not found");
// 	else if (cmds->exit_status == 1)
// 		puts("No such file or directory");
// 	else if (cmds->exit_status == 126)
// 		puts("is a directory");
// 	else if (cmds->exit_status == 130)
// 		puts("CTRL-C");
// 	else if (cmds->exit_status == 131)
// 		puts("CTRL-/");
// 	return (cmds->exit_status);
// }

char	*get_env_val(t_cmds *cmds, char *join_arg)
{
	int		j;
	int		k;
	int		i;
	char	arg;

	i = 0;
	j = 0;
	k = 0;
	//puts("hi");
	arg = *join_arg;
	if (cmds->env_val)
		free(cmds->env_val);
	cmds->env_val = ft_strdup(join_arg + 1);
	while (cmds->envir[j] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[j], '=');
		if (ft_strcmp(cmds->env_line[0], cmds->env_val) == 0)
		{
			k = 1;
			return (cmds->env_line[1]);
		}
		j++;
	}
	if (k == 0)
	{
		if (!ft_strcmp(cmds->join_arg, "$"))
			return (ft_strdup("$"));
		else if (!ft_strcmp(cmds->join_arg, "$?"))
		{
			//get_exit_status(cmds);
			exit(0);
		}
		while (cmds->join_arg[++i])
			if (ft_isalpha(cmds->join_arg[i]))
			 	return (ft_strdup(""));
		return (cmds->join_arg);
	}
	return (NULL);
}

int		b_point(char *arg)
{
	int i;

	i = 0;
	while (arg[++i])
		if (ft_strchr("$\\\"';| ", arg[i]))
			return (i);
	return (i);
}

char	*parse_dollar(t_cmds *cmds, char **line_list)
{
	int			i;
	int			l;
	char		*tmp;
	char		*tmp1;
	char		tmp2[2];
	char		*arg;
	char		is_in_dq;

	tmp = NULL;
	tmp1 = NULL;
	is_in_dq = 0;
	arg = ft_strdup("");
	i = -1;
	cmds->quote = 0;
    cmds->ignore = 0;
	while ((*line_list)[++i])
	{
		if ((*line_list)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && (*line_list)[i] == '"' && !cmds->quote)
			is_in_dq = !is_in_dq;
		if (!is_in_dq && !cmds->ignore && is_quote((*line_list)[i]) == 1)
			cmds->quote = quote_activer((*line_list)[i], cmds->quote);
		if ((*line_list)[i] == '$' && is_quote((*line_list)[i + 1]) &&
		!cmds->ignore && ((i && !is_quote((*line_list)[i - 1])) || !i))
			i++;
		if ((*line_list)[i] == '$' && !cmds->ignore && !cmds->quote)
		{
			l = b_point(*line_list + i);
			cmds->join_arg = ft_substr(*line_list + i, 0, l);
			cmds->env_val = get_env_val(cmds, cmds->join_arg);
			tmp = ft_strjoin(arg, cmds->env_val);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp);
			i += l - 1;
		}
		else
		{
			tmp2[0] = (*line_list)[i];
			tmp2[1] = '\0';
			tmp1 = ft_strjoin(arg, tmp2);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp1);
		}
		((*line_list)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	*line_list = ft_strdup(arg);
	(arg) ? free(arg) : 0;
	(tmp) ? free(tmp) : 0;
	(tmp1) ? free(tmp1) : 0;
	return (*line_list);
}
