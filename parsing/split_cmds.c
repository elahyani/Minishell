/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:18:50 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/11 13:14:47 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	j = -1;
	cmds->quote = 0;
	cmds->ignore = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote(str[i]))
			cmds->quote = quote_activer(str[i], cmds->quote);
		if (str[i] == x && j != -1 && !cmds->quote && !cmds->ignore)
		{
			if (!(split[k++] = ft_substr(str, j, i - j)))
				return (ft_free(split));
			j = -1;
		}
		else if (str[i] != x && j == -1)
			j = i;
		(str[i] != '\\' && cmds->ignore) ? cmds->ignore = 0 : 0;
	}
	if (j != -1)
		if (!(split[k] = ft_substr(str, j, i - j)))
			return (ft_free(split));
	return (split);
}

static int		len_arg(char *str, char c, t_cmds *cmds)
{
	int			i;
	int			start;
	int			len;

	i = -1;
	len = 0;
	start = 0;
	cmds->quote = 0;
	cmds->ignore = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && cmds->quote != 1)
			cmds->ignore = cmds->ignore ? 0 : 1;
		if (!cmds->ignore && is_quote(str[i]))
			cmds->quote = quote_activer(str[i], cmds->quote);
		if (str[i] == c && !cmds->ignore && !cmds->quote)
		{
			if (start == 1)
			{
				len++;
				start = 0;
			}
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
