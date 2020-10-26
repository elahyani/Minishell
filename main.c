/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/10/26 20:32:23 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(char	**line)
{	
	int		len;
	int		len1;
	int		i;
	char	**cmd;
	int		counter;

	counter = 0;
	i = 0;
	len = ft_strlen(*line);	
	// printf("%s | %d\n", *line, len);
	while (*line[i] <= len)
	{
		(*line[i] == ' ') ? counter += 1 : 0;
	}
	cmd = ft_split(*line, ' ');
	while (i < counter)
	{
		printf("%s\n", cmd[i]);
		i++;
	}
	printf("%s\n", cmd[i]);
}

int		main()
{
	char	*line;

	dprintf(0, "minishell>");
	while ((get_next_line(0, &line)) > 0)
	{
		parse_line(&line);
		dprintf(0, "minishell>");
		free(line);
	}
	return (0);
}