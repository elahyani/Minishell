/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:46:24 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/26 09:08:27 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			wait_child(t_cmds *cmds, pid_t pid)
{
	int i;
	int status;

	i = -1;
	if (!cmds->num_pipe)
		waitpid(pid, &status, 0);
	else
	{
		while (++i < cmds->num_pipe + 1)
			waitpid(cmds->pipe.pids[i], &status, 0);
	}
	return (status);
}

void		get_cmd_help(t_cmds *cmds, pid_t pid)
{
	int		status;

	status = 0;
	close_pipes(cmds->pipe.fds, cmds->num_pipe);
	status = wait_child(cmds, pid);
	if (status == 2 || status == 3)
		cmds->ret = status + 128;
	else
	{
		if (WIFEXITED(status))
			cmds->ret = WEXITSTATUS(status);
	}
	if (cmds->num_pipe)
	{
		free(cmds->pipe.fds);
		free(cmds->pipe.pids);
	}
}

int			exec_cmds(t_cmds *cmds, t_cmd_list *list)
{
	int		ret;

	ret = 1;
	if (ft_strcmp(list->args[0], "cd") == 0)
		ret = cmd_cd(list, cmds);
	else if (ft_strcmp(list->args[0], "pwd") == 0)
		ret = cmd_pwd(cmds);
	else if (ft_strcmp(list->args[0], "export") == 0)
		ret = cmd_export(list, cmds);
	else if (ft_strcmp(list->args[0], "unset") == 0)
		ret = cmd_unset(list, cmds);
	else if (ft_strcmp(list->args[0], "exit") == 0)
		ret = cmd_exit(list, cmds);
	else if (ft_strcmp(list->args[0], "echo") == 0)
		ret = cmd_echo(list);
	else if (ft_strcmp(list->args[0], "env") == 0)
		ret = cmd_env(cmds, list);
	else
		check_cmd(cmds, list);
	cmds->ret = ret;
	return (ret);
}

t_cmd_list	*starting_execution(t_cmds *cmds, t_cmd_list *list)
{
	pid_t	pid;

	if ((list->next && !list->end) || !is_builtin(list->args[0]))
	{
		cmds->pipe.fds = pipe_file_des(cmds->num_pipe, cmds->pipe.fds);
		save_file_des(cmds->pipe.backup);
		cmds->pipe.file_num = 0;
		while (list)
		{
			pid = exec_child(cmds, list);
			list = skip_redir(list);
			cmds->pipe.file_num += 2;
			if (list->end)
				break ;
			list = list->next;
		}
		create_io_fds_cpy(cmds->pipe.backup);
		get_cmd_help(cmds, pid);
	}
	else if (list->args[0])
		cmds->ret = exec_cmds(cmds, list);
	return (list);
}

t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	cmds->num_pipe = get_num_pipes(head);
	cmds->pipe.file_num = 0;
	if (cmds->num_pipe)
		cmds->pipe.pids = malloc(sizeof(int) * (cmds->num_pipe + 1));
	head = starting_execution(cmds, head);
	return (head);
}
