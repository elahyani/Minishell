/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:45:33 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/08 14:26:44 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <string.h>

void	ft_putnbr_fd(int n, int fd)
{
	long nb;

	nb = n;
	if (nb < 0)
	{
		putchar('-');
		nb = nb * -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		putchar(nb % 10 + '0');
	}
	else
	{
		putchar(nb + '0');
	}
}


char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		j;
	size_t		s_len;

	j = 0;
	if (!s)
		return (NULL);
	s_len = strlen(s);
	if (start > s_len)
		return (strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	if (!(sub = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (j < len)
	{
		sub[j] = s[start];
		start++;
		j++;
	}
	sub[j] = '\0';
	return (sub);
}

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
	len = strlen(str);
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
	size_t	len;
	size_t	k;

	k = 0;
	len = 0;
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
	return (trim);
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
	while (str[++j])
	{
		if (str[j] == q && ((j && str[j - 1] != '\\') || !j))
			break ;
	}
	if (str[j])
		return (j);
	return (-1);
}

static char		**ft_index(char **split, char *str, char x)
{
	int i;
	int j;
	int k;
	int q;

	i = -1;
	k = 0;
	j = -1;
	q = -1;
	while (str[++i])
	{
		if (strchr("\"'", str[i]) && ((i && str[i - 1] != '\\') || !i))
		{	j = i;
			i += check_for_q(str, i);
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
		if (strchr("\"'", str[i]) && ((i && str[i - 1] != '\\') || !i))
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

char			**split_q(char const *str, char c)
{
	char		**res;
	size_t		len;
	int			i;
	int			j;

	j = 0;
	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	len = len_wrd((char *)str, c);
	ft_putnbr_fd((int)len, 1);
	putchar('\n');
	if (!(res = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	res = ft_index(res, (char *)str, c);
	while (i < len)
	{
		res[i] = ft_strtrim(res[i], "\"'");
		printf("res[%d] = |%s|\n", i, res[i]);
		i++;
	}
	if (!res)
		return (NULL);
	res[len] = 0;
	return (res);
}

int		main(void)
{
	int		i;
	char	**split;
	char	*cmd;
	
	cmd = "echo hhhhhhhhhhhhhhhhhh";
	split = split_q(cmd, ' ');
	i = -1;
	while (split[++i])
		printf("srg[%d] = |%s|\n", i, split[i]);
}