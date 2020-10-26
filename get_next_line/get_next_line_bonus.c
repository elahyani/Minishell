/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 00:06:08 by elahyani          #+#    #+#             */
/*   Updated: 2019/12/21 16:47:07 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_line(char *str)
{
	int		i;

	i = -1;
	while (str[++i] && str[i] != '\n')
		;
	return (i);
}

char	*del(char *str, char *data)
{
	if (str)
		free(str);
	str = data;
	return (str);
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

int		check_line(char **p, char **line, int fd)
{
	int		i;
	char	*tmp;

	if (p[fd])
	{
		if (ft_strchr(p[fd], '\n'))
		{
			i = ft_line(p[fd]);
			*line = del(*line, ft_substr(p[fd], 0, i));
			p[fd] = del(p[fd], ft_strdup(p[fd] + i + 1));
			if (!(*line) || !(p[fd]))
				return (free_err(line, NULL, p[fd]));
			return (1);
		}
		else if (ft_strlen(p[fd]))
		{
			if (!(tmp = (*line) ? ft_strjoin(*line, p[fd]) : ft_strdup(p[fd])))
				return (free_err(line, NULL, p[fd]));
			*line = del(*line, tmp);
			p[fd] = del(p[fd], NULL);
			return (0);
		}
		free(p[fd]);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			r;
	char		*buff;
	char		*tmp;
	static char	*ptr[FD_NUM];

	if (fd < 0 || fd > FD_NUM || !line || read(fd, NULL, 0) < 0 ||
	!(tmp = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	*line = ft_strdup("");
	while ((r = read(fd, tmp, BUFFER_SIZE)))
	{
		tmp[r] = '\0';
		if (!(buff = (ptr[fd]) ? ft_strjoin(ptr[fd], tmp) : ft_strdup(tmp)))
			return (free_err(line, buff, ptr[fd]));
		ptr[fd] = del(ptr[fd], buff);
		free(tmp);
		if (ft_strchr(ptr[fd], '\n'))
			break ;
		if (!(tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (free_err(line, buff, ptr[fd]));
	}
	(r == 0) ? free(tmp) : 0;
	return (check_line(ptr, line, fd));
}
