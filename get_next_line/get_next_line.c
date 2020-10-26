/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 19:28:35 by elahyani          #+#    #+#             */
/*   Updated: 2019/12/21 15:56:03 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_line(char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		;
	return (i);
}

int		free_err(char **line, char *buff, char *ptr)
{
	if (*line)
		free(*line);
	if (buff)
		free(buff);
	if (ptr)
		free(ptr);
	return (-1);
}

char	*del(char *str, char *data)
{
	if (str)
		free(str);
	str = data;
	return (str);
}

int		check_line(char **p, char **line)
{
	int		i;
	char	*tmp;

	if (*p)
	{
		if (ft_strchr(*p, '\n'))
		{
			i = ft_line(*p);
			*line = del(*line, ft_substr(*p, 0, i));
			*p = del(*p, ft_strdup(*p + i + 1));
			if (!(*line) || !(*p))
				return (free_err(line, NULL, *p));
			return (1);
		}
		else if (ft_strlen(*p))
		{
			if (!(tmp = (*line) ? ft_strjoin(*line, *p) : ft_strdup(*p)))
				return (free_err(line, NULL, *p));
			*line = del(*line, tmp);
			*p = del(*p, NULL);
			return (0);
		}
		free(*p);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			r;
	char		*tmp;
	char		*buff;
	static char	*ptr;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0 ||
		!(tmp = malloc(sizeof(char *) * (BUFFER_SIZE + 1))))
		return (-1);
	*line = ft_strdup("");
	while ((r = read(fd, tmp, BUFFER_SIZE)))
	{
		tmp[r] = '\0';
		if (!(buff = (ptr) ? ft_strjoin(ptr, tmp) : ft_strdup(tmp)))
			return (free_err(line, buff, ptr));
		ptr = del(ptr, buff);
		free(tmp);
		if (ft_strchr(ptr, '\n'))
			break ;
		if (!(tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (free_err(line, buff, ptr));
	}
	if (r == 0)
		free(tmp);
	return (check_line(&ptr, line));
}
