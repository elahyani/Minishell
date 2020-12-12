/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:45:33 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/12 11:59:33 by ichejra          ###   ########.fr       */
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
		if (str[i] == c)
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
	if (!res)
		return (NULL);
	res[len] = 0;
	return (res);
}
