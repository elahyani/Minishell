/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:18:50 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/10 14:24:21 by elahyani         ###   ########.fr       */
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

static char		**ft_index(char **split, char *str, char x)
{
	int i;
	int j;
	int k;
	int ignore;
	int	quote;

	i = -1;
	k = 0;
	j = -1;
	quote = 0;
	ignore = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && quote != 1)
			ignore = ignore ? 0 : 1;
		if (!ignore && is_quote(str[i]))
			quote = quote_activer(str[i], quote);
		if (str[i] == x && j != -1 && !quote && !ignore)
		{
			if (!(split[k++] = ft_substr(str, j, i - j)))
				return (ft_free(split));
			j = -1;
		}
		else if (str[i] != x && j == -1)
			j = i;
		if (str[i] != '\\' && ignore)
			ignore = 0;
	}
	if (j != -1)
		if (!(split[k] = ft_substr(str, j, i - j)))
			return (ft_free(split));
	return (split);
}

static int		len_wrd(char *str, char c)
{
	int			i;
	int			start;
	int			len;
	int			quote;
	int			ignore;

	i = 0;
	len = 0;
	start = 0;
	quote = 0;
	ignore = 0;
	while (str[i])
	{
		if (str[i] == '\\' && quote != 1)
			ignore = ignore ? 0 : 1;
		if (!ignore && is_quote(str[i]))
			quote = quote_activer(str[i], quote);
		if (str[i] == c && !ignore && !quote)
		{
			if (start == 1)
			{
				len++;
				start = 0;
			}
		}
		else if (str[i] != c)
			start = 1;
		if (str[i] != '\\' && ignore)
			ignore = 0;
		i++;
	}
	if (start)
		len++;
	return (len);
}

char			**split_cmd(char const *str, char c)
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
	len = len_wrd((char *)str, c);
	if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	res = ft_index(res, (char *)str, c);
	while (++i < (int)len)
		res[i] = ft_remove_quotes(res[i]);
	if (!res)
		return (NULL);
	res[len] = 0;
	return (res);
}
