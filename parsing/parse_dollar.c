/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:43:24 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/22 10:15:27 by elahyani         ###   ########.fr       */
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

void	parse_dollar_init(t_cmds **cmds, int *i, int *l, int *is_in_dq)
{
	*i = -1;
	*l = 0;
	*is_in_dq = 0;
	(*cmds)->tmp_d = NULL;
	(*cmds)->tmp1_d = NULL;
	(*cmds)->quote = 0;
    (*cmds)->ignore = 0;
	(*cmds)->arg_d = ft_strdup("");
}

// void	manag_quotes_d(char **line_list, t_cmds **cmds, int *i, int *is_in_dq)
// {
// 	if ((*line_list)[*i] == '\\' && (*cmds)->quote != 1)
// 		(*cmds)->ignore = (*cmds)->ignore ? 0 : 1;
// 	if (!(*cmds)->ignore && (*line_list)[*i] == '"' && !(*cmds)->quote)
// 		*is_in_dq = !(*is_in_dq);
// 	if (!(*is_in_dq) && !(*cmds)->ignore && is_quote((*line_list)[*i]) == 1)
// 		(*cmds)->quote = quote_activer((*line_list)[*i], (*cmds)->quote);
// 	if ((*line_list)[*i] == '$' && is_quote((*line_list)[*i + 1]) &&
// 	!(*cmds)->ignore && ((*i && !is_quote((*line_list)[*i - 1])) || !(*i)))
// 		(*i)++;
// }

// void	set_env_val()
// {
	
// }

char	*parse_dollar(t_cmds *cmds, char **line_list)
{
	int			i;
	int			l;
	int			is_in_dq;

	parse_dollar_init(&cmds, &i, &l, &is_in_dq);
	while ((*line_list)[++i])
	{
		// fct 1
		if ((*line_list)[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && (*line_list)[i] == '"' && !cmds->quote)
			is_in_dq = !is_in_dq;
		if (!is_in_dq && !cmds->ignore && is_quote((*line_list)[i]) == 1)
			cmds->quote = quote_activer((*line_list)[i], cmds->quote);
		if ((*line_list)[i] == '$' && is_quote((*line_list)[i + 1]) &&
		!cmds->ignore && ((i && !is_quote((*line_list)[i - 1])) || !i))
			i++;
		// manag_quotes_d(line_list, &cmds, &i, &is_in_dq);
		if ((*line_list)[i] == '$' && !cmds->ignore && !cmds->quote)
		{
			// fct 2
			l = b_point(*line_list + i);
			cmds->join_arg = ft_substr(*line_list + i, 0, l);
			cmds->env_val = get_env_val(cmds, cmds->join_arg);
			ft_free_str(cmds->join_arg);
			cmds->tmp_d = ft_strjoin(cmds->arg_d, cmds->env_val);
			ft_free_str(cmds->env_val);
			ft_free_str(cmds->arg_d);
			cmds->arg_d = cmds->tmp_d;
			i += l - 1;
		}
		else
		{
			cmds->tmp2_d[0] = (*line_list)[i];
			cmds->tmp2_d[1] = '\0';
			cmds->tmp1_d = ft_strjoin(cmds->arg_d, cmds->tmp2_d);
			ft_free_str(cmds->arg_d);
			cmds->arg_d = cmds->tmp1_d;
		}
		((*line_list)[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	return (cmds->arg_d);
}
