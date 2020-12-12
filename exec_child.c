/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:26:16 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/12 20:03:41 by ichejra          ###   ########.fr       */
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

/* static t_cmd_list *skip_append(t_cmd_list *list)
{
	while (list && list->redir > 0)
	{
		if (!list->next)
			break ;
		list = list->next;
	}
	return (list);
} */

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
	//int j;
	char *file;
	struct stat file_stat;

	i = -1;
	//list = skip_append(list);
	/* while (ft_strcmp(list->args[i], "<"))
		i++; */
	//printf("========|%s|\n", list->args[1]);
	list->args = split_cmd(list->data, ' ', cmds);
	//printf("========|%s|\n", list->next->args[0]);
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

void	exec_io_redi(t_cmds *cmds, t_cmd_list *list)
{
	int k;
	k = 0;
	t_cmd_list *tmp;
	tmp = list;
	while (tmp && tmp->redir)
	{
		if (tmp->redir == '>' || tmp->redir == 'a')
		{
			//cmds->pipe.fdout = forward_redir();
			//if (!cmds->pipe.fdout)
			k = 4;
				
		}
		else if (tmp->redir == '<')
		{
			cmds->pipe.fdin = backward_redir(tmp->next, cmds);
			//if (!cmds->pipe.fdin)
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
			//printf("j====|%d|\n", errno);
			ft_putstr_fd("dup2 Error", 1);
			exit(1);
			
		}
	}
	// printf("%d\n", list->p);
	//if (list->next && ((((!list->start && !list->end) || (!list->start && list->end)) || (!list->next->end))))
	if (list->next && !list->end && (list->p || !list->next->end))
	{
		// puts("here");
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
	char *path;
	int ret = 0;
	pid = fork();
	if (pid == 0)
	{
		//printf("am a child wlh\n");
		cmds->pipe.fdin = 0;
		cmds->pipe.fdout = 0;
		(cmds->num_pipe) ? cmds->pipe.fds = create_fds(list, cmds,cmds->pipe.file_num, cmds->pipe.fds) : 0;
		// puts("here --------------------------------");
		close_pipes(cmds->pipe.fds, cmds->num_pipe);
		// if (list->prev->redir)
		if (list->redir)
		{
			// puts("am in");
			exec_io_redi(cmds, list);
		}
		// list->args = split_cmd(list->data, ' ', cmds);
		// printf("%s\n", list->args[0]);
		//&& list->prev && !list->prev->redir
		if (list->args[0] && (!list->prev || (list->prev  && !list->prev->redir)))
		{
			// puts("yayayay");
			// printf("list === |%s|\n", list->args[0]);
			if (ft_strcmp(list->args[0], "cd") == 0)
				cmd_cd(list, cmds);
			else if (ft_strcmp(list->args[0], "pwd") == 0)
				cmd_pwd(cmds);
			else if (ft_strcmp(list->args[0], "export") == 0)
				cmd_export(list, cmds);
			else if (ft_strcmp(list->args[0], "unset") == 0)
				cmd_unset(list, cmds);
			else if (ft_strcmp(list->args[0], "exit") == 0)
				cmd_exit();
			else if (ft_strcmp(list->args[0], "echo") == 0)
				cmd_echo(list);
			else if (ft_strcmp(list->args[0], "env") == 0)
				cmd_env(cmds, list);
			else
			{
				path = get_bin_path(list->args[0], cmds->envir);
				ret = execve(path, list->args, cmds->envir);
				//printf("\npat=|%d|\n", ret);
				if (ret < 0)
				{
					ft_putstr_fd("minishell: ", 1);
					ft_putstr_fd(list->args[0], 1);
					ft_putendl_fd(": command not found", 1);
					exit(1); //function that returns code error
				}
			}
		}
		exit(0);
	}
	else if (pid < 0)
	{
		ft_putstr_fd("Fork error", 1);
		//exit(0);
	}
	if (cmds->num_pipe)
		cmds->pipe.pids[cmds->pipe.file_num / 2] = pid;
	return (pid);
}