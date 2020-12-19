/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:50:06 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/19 12:20:44 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*rm_left(const char *str, const char *set)
{
	int j;

	j = 0;
	while (set[j])
	{
		if (set[j] == *str)
		{
			str++;
			j = 0;
		}
		else
			j++;
	}
	return (str);
}

static size_t		rm_right(char const *str, char const *set)
{
	int		j;
	size_t	len;

	j = 0;
	len = ft_strlen(str);
	while (set[j] && len)
	{
		if (set[j] == str[len - 1])
		{
			len--;
			j = 0;
		}
		else
			j++;
	}
	return (len);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	char	*tmp;
	size_t	len;
	size_t	k;

	k = 0;
	len = 0;
	tmp = (char*)s1;
	if (!s1)
		return (NULL);
	s1 = rm_left(s1, set);
	if (*s1)
		len = rm_right(s1, set);
	if (!(trim = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (k < len)
	{
		trim[k] = s1[k];
		k++;
	}
	trim[k] = '\0';
	(tmp) ? free(tmp) : 0;
	return (trim);
}
