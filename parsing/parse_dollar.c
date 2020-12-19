/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:24 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/19 10:26:47 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_str(char *str)
{
	if (str)
		free(str);
}

char	*get_env_val(t_cmds *cmds, char *join_arg)
{
	int		j;
	char	*env_val_w;


	j = 0;
	env_val_w = NULL;
	while (cmds->envir[j] != NULL)
	{
		env_val_w = ft_get_first(cmds->envir[j], '=');
		if (ft_strcmp(env_val_w, join_arg + 1) == 0)
		{
			ft_free_str(env_val_w);
			return (ft_strdup(cmds->envir[j] + ft_strlen(join_arg + 1) + 1));
		}
		ft_free_str(env_val_w);
		j++;
	}
	if (!ft_strcmp(cmds->join_arg, "$"))
		return (ft_strdup("$"));
	else if (cmds->join_arg[1] == '?')
		return (ft_itoa(cmds->ret));
	j = 0;
	while (cmds->join_arg[++j])
		if (ft_isalpha(cmds->join_arg[j]))
			return (ft_strdup(""));
	return (ft_strdup(cmds->join_arg));
}

int		b_point(char *arg)
{
	int i;

	i = 0;
	if (arg[i + 1] == '?')
		return (i + 2);
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
			ft_free_str(cmds->join_arg);
			tmp = ft_strjoin(arg, cmds->env_val);
			ft_free_str(cmds->env_val);
			ft_free_str(arg);
			arg = tmp;
			i += l - 1;
		}
		else
		{
			tmp2[0] = (*line_list)[i];
			tmp2[1] = '\0';
			tmp1 = ft_strjoin(arg, tmp2);
			ft_free_str(arg);
			arg = tmp1;
		}
		((*line_list)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	return (arg);
}
