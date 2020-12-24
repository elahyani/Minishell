/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:26:16 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:48:39 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		redir_fd_io(t_cmds *cmds)
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

pid_t		exec_child(t_cmds *cmds, t_cmd_list *list)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cmds->pipe.fdin = 0;
		cmds->pipe.fdout = 0;
		(cmds->num_pipe) ? cmds->pipe.fds = create_fds(list,
			cmds->pipe.file_num, cmds->pipe.fds) : 0;
		close_pipes(cmds->pipe.fds, cmds->num_pipe);
		if (list->redir)
			exec_io_redi(cmds, list);
		if (list->args[0] && (!list->prev ||
			(list->prev && !list->prev->redir)))
			cmds->ret = exec_cmds(cmds, list);
		exit(0);
	}
	else if (pid < 0)
		exit_error("Fork error", 1, cmds, list);
	if (cmds->num_pipe)
		cmds->pipe.pids[cmds->pipe.file_num / 2] = pid;
	return (pid);
}
