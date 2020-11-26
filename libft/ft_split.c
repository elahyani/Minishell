/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:45:33 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/26 14:29:38 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
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

	i = -1;
	k = 0;
	j = -1;
	while (str[++i])
	{
		if (ft_strchr("\"'", str[i]) && ((i && str[i - 1] != '\\') || !i))
		{	
			if (j == -1)
				j = i;
			i += check_for_q(str, i);
			if (str[i + 1] && ft_strchr("\"'", str[i + 1]))
                continue ;
		}
		if (str[i] == x && j != -1)
		{
			if (!(split[k++] = ft_substr(str, j, i - j)))
				return (ft_free(split));
			j = -1;
		}
		else if (str[i] != x && j == -1)
			j = i;
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

	i = 0;
	len = 0;
	start = 0;
	while (str[i])
	{
		if (ft_strchr("\"'", str[i]) && ((i && str[i - 1] != '\\') || !i))
			i += check_for_q(str, i);
		if (str[i] == c && ((i && str[i - 1] != '\\') || !i))
		{
			if (start == 1)
			{
				len++;
				start = 0;
			}
		}
		else if (str[i] != c)
			start = 1;
		i++;
	}
	if (start)
		len++;
	return (len);
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
	// while (++i < (int)len)
	// 	res[i] = ft_strtrim(res[i], "\"'");
	if (!res)
		return (NULL);
	res[len] = 0;
	return (res);
}