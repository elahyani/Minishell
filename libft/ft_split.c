/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:45:33 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/10 11:11:03 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		is_quote(int c)
{
	if (c == '\"')
		return (2);
	else if (c == '\'')
		return (1);
	return (0);
}

int		quote_activer(int c, int quote)
{
	if (is_quote(c) && !quote)
		return (is_quote(c));
	else if (quote && is_quote(c) == quote)
		return (0);
	else
		return (quote);
}

static char		**ft_free(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

int			check_for_q(char *str, int j)
{
	char	q;

	str += j;
	j = 0;
	q = *str;
	if (q == '"') {
        while (str[++j])
            if (str[j] == q && ((j && str[j - 1] != '\\') || !j))
                break;
    }
	else
        while (str[++j])
            if (str[j] == q)
                break;
	if (str[j])
		return (j);
	return (-1);
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

char	*ft_remove_quotes(char *res)
{
	int		i;
	int		j;
	int 	quote;
	int		ignore;

	i = 0;
	quote = 0;
	ignore = 0;
	while (res[i])
	{
		j = 0;
		if (res[i] == '\\' && quote != 1)
			ignore = ignore ? 0 : 1;
		if (((!quote || (quote && is_quote(res[i]) == quote)) && is_quote(res[i]) && !ignore))
		{
			j = i - 1;
			quote = quote_activer(res[i], quote);
			while (res[++j])
				res[j] = res[j + 1];
		}
		else if (ignore)
		{
			j = i - 1;
			while (res[++j])
				res[j] = res[j + 1];
		}
		(!j || ignore) ? i++ : 0;
		(res[i] != '\\' && ignore) ? ignore = 0 : 0;
	}
	return (res);
}

char			**ft_split(char const *str, char c)
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
