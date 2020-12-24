/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:47:15 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:49:03 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		open_input(char *file)
{
	int			fd;

	fd = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_putendl_fd("error opening file", 1);
		exit(1);
	}
	return (fd);
}

static int		backward_redir(t_cmd_list *list)
{
	int			i;
	char		*file;
	struct stat	file_stat;

	i = -1;
	while (list->args[++i])
	{
		file = list->args[i];
		if (stat(file, &file_stat) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(file, 1);
			ft_putendl_fd(": No such file or directory", 1);
			exit(1);
		}
	}
	return (open_input(file));
}

static int		open_output(t_cmd_list *list, char redir)
{
	int			fd;
	int			flag;
	int			flag_mode;

	fd = 0;
	flag = O_WRONLY | O_CREAT;
	flag_mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
	if (redir == 'a')
		flag = flag | O_APPEND;
	else if (redir == '>')
		flag = flag | O_TRUNC;
	if ((fd = open(list->args[0], flag, flag_mode)) < 0)
	{
		ft_putendl_fd("error opening file", 1);
		exit(1);
	}
	return (fd);
}

static int		forward_redir(t_cmd_list *tmp, t_cmd_list *list)
{
	int			i;

	if (ft_arr_len(tmp->next->args) > 1 && !tmp->next->start)
	{
		i = 1;
		while (tmp->next->args[i])
		{
			list->args = ft_get_arr(tmp->next->args[i], list->args);
			i++;
		}
	}
	return (open_output(tmp->next, tmp->redir));
}

void			exec_io_redi(t_cmds *cmds, t_cmd_list *list)
{
	t_cmd_list	*tmp;

	tmp = list;
	while (tmp && tmp->redir)
	{
		if (tmp->redir == '>' || tmp->redir == 'a')
		{
			cmds->pipe.fdout = forward_redir(tmp, list);
			if (!cmds->pipe.fdout)
				cmds->ret = 1;
		}
		else if (tmp->redir == '<')
		{
			cmds->pipe.fdin = backward_redir(tmp->next);
			if (!cmds->pipe.fdin)
				cmds->ret = 1;
		}
		tmp = tmp->next;
	}
	redir_fd_io(cmds);
}
