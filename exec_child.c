/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:26:16 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/18 11:35:15 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//////////////redir//////////////////////////

void	redir_fd_io(t_cmds *cmds)
{
	if (cmds->pipe.fdout)
	{
		dup2(cmds->pipe.fdout, 1);
		close(cmds->pipe.fdout);
	}
	if (cmds->pipe.fdin)
	{
		dup2(cmds->pipe.fdin, 0);
		close(cmds->pipe.fdin);
	}
}

int open_input(char *file)
{
	int fd;

	fd = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		ft_putendl_fd("error opening file", 1);
		exit(1);
	}
	return (fd);
}


int		backward_redir(t_cmd_list *list, t_cmds *cmds)
{
	int i;
	char *file;
	struct stat file_stat;

	i = -1;
	list->args = split_cmd(list->data, ' ', cmds);
	while (list->args[++i])
	{
		file = list->args[i];
		if (stat(file, &file_stat) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(file, 1);
			ft_putendl_fd(": No such file or directory", 1);
			exit (1);
		}
	}
	return (open_input(file));
	
}

int		open_output(t_cmd_list *list, char redir)
{
	int fd;
	int flag;
	int flag_mode;

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

int		forward_redir(t_cmd_list *tmp, t_cmd_list *list, t_cmds *cmds)
{
	int i;
	
	tmp->next->args = split_cmd(list->next->data, ' ', cmds);
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

void	exec_io_redi(t_cmds *cmds, t_cmd_list *list)
{
	t_cmd_list *tmp;
	tmp = list;
	while (tmp && tmp->redir)
	{
		if (tmp->redir == '>' || tmp->redir == 'a')
		{
			cmds->pipe.fdout = forward_redir(tmp, list, cmds);
			if (!cmds->pipe.fdout)
				cmds->ret = 1;
				
		}
		else if (tmp->redir == '<')
		{
			cmds->pipe.fdin = backward_redir(tmp->next, cmds);
			if (!cmds->pipe.fdin)
				cmds->ret = 1;
		}
		tmp = tmp->next;
	}
	redir_fd_io(cmds);
}


//////////////redir//////////////////////////

static void	close_pipes(int *fds, int num_pipe)
{
	int		i;

	i = 0;
	while (i < 2 * num_pipe)
		close(fds[i++]);
}

int		*create_fds(t_cmd_list *list, t_cmds *cmds,int j, int *fds)
{
	int num = 1;
	if (cmds->num_pipe)	
		num = 2;
	if (j != 0)
	{
		if (dup2(fds[j - 2], 0) < 0)
		{
			ft_putstr_fd("dup2 Error", 1);
			exit(1);
			
		}
	}
	if (list->next && !list->end && (list->p || !list->next->end))
	{
		if (dup2(fds[j + 1], 1) < 0)
		{
			ft_putstr_fd("dup2 Error", 1);
			exit(1);
		}
	}
	return (fds);
}

pid_t			exec_child(t_cmds *cmds, t_cmd_list *list)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cmds->pipe.fdin = 0;
		cmds->pipe.fdout = 0;
		(cmds->num_pipe) ? cmds->pipe.fds = create_fds(list,
			cmds,cmds->pipe.file_num, cmds->pipe.fds) : 0;
		close_pipes(cmds->pipe.fds, cmds->num_pipe);
		if (list->redir)
			exec_io_redi(cmds, list);
		if (list->args[0] && (!list->prev ||
			(list->prev  && !list->prev->redir)))
		{
			cmds->ret = exec_cmds(cmds, list);
			printf("2ret====|%d|\n", cmds->ret);
		}
		exit(0);
	}
	else if (pid < 0)
		exit_error("Fork error", 1, cmds, list);
	if (cmds->num_pipe)
		cmds->pipe.pids[cmds->pipe.file_num / 2] = pid;
	return (pid);
}