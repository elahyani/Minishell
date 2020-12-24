/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:18:50 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 12:48:07 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char		**ft_free(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

static char		**ft_sp_index(char **split, char *str, char x, t_cmds *cmds)
{
	int k;

	k = 0;
	cmds->i = -1;
	cmds->j = -1;
	cmds->quote = 0;
	cmds->ignore = 0;
	while (str[++cmds->i])
	{
		check_for_quote(&cmds, &str, &cmds->i);
		if (str[cmds->i] == x && cmds->j != -1 && !cmds->quote && !cmds->ignore)
		{
			if (!(split[k++] = ft_substr(str, cmds->j, cmds->i - cmds->j)))
				return (ft_free(split));
			cmds->j = -1;
		}
		else if (str[cmds->i] != x && cmds->j == -1)
			cmds->j = cmds->i;
		(str[cmds->i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	if (cmds->j != -1)
		if (!(split[k] = ft_substr(str, cmds->j, cmds->i - cmds->j)))
			return (ft_free(split));
	return (split);
}

static int		len_arg(char *str, char c, t_cmds *cmds)
{
	int			i;
	int			len;
	int			start;

	i = -1;
	len = 0;
	start = 0;
	cmds->quote = 0;
	cmds->ignore = 0;
	while (str[++i])
	{
		check_for_quote(&cmds, &str, &i);
		if (str[i] == c && !cmds->ignore && !cmds->quote && start == 1)
		{
			len++;
			start = 0;
		}
		else if (str[i] != c)
			start = 1;
		(str[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	(start) ? len++ : 0;
	return (len);
}

char			**split_cmd(char const *str, char c, t_cmds *cmds)
{
	char		**res;
	size_t		len;
	int			i;
	int			j;

	j = 0;
	i = -1;
	len = 0;
	if (!str)
		return (NULL);
	len = len_arg((char *)str, c, cmds);
	if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	res = ft_sp_index(res, (char *)str, c, cmds);
	while (++i < (int)len)
		res[i] = ft_remove_quotes(res[i]);
	if (!res)
		return (NULL);
	res[len] = 0;
	return (res);
}
