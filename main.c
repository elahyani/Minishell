/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/12 20:02:43 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


////////////////////////////////////////////

int		ft_access(char *path, int mode)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) < 0)
		return (0);
	if (mode == 1)
		return (file_stat.st_mode & S_IXUSR ? 1 : 0);
	else if (mode == 2)
		return (file_stat.st_mode & S_IWUSR ? 1 : 0);
	else if (mode == 4)
		return (file_stat.st_mode & S_IRUSR ? 1 : 0);
	return (0);
}

char	*try_path(char *cmd, char *dir)
{
	char	*path;
	int		len;

	len = ft_strlen(cmd) + ft_strlen(dir) + 2;
	if (!(path = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	if (ft_access(path, 1) == 1)
		return (path);
	free(path);
	return (NULL);
}


char	*get_bin_path(char *cmdfile, char **env)
{
	char	*path;
	int		i;
	char	**split_path;
	char	*acc_path;

	path = NULL;
	split_path = NULL;
	i = 0;
	if ((i = ft_getenv("PATH", env)) >= 0)
		path = env[i] + 5;
	if (path && (split_path = ft_split(path, ':')))
	{
		i = 0;
		while (split_path[i])
		{
			if ((acc_path = try_path(cmdfile, split_path[i])))
			{
				//ft_free_arr(split_path);
				return (acc_path);
			}
			i++;
		}
	}
	//ft_free_arr(split_path);
	return (cmdfile);
}


////////////////////////////////////////////



// fds[0] = dup(0);
// fds[1] = dup(1);
// fds[2] = dup(2);


int		*pipe_fds(int num_pipe, int *fds)
{
	int		i;

	i = -1;
	if (!num_pipe)
		return (NULL);
	if (!(fds = (int *)malloc(sizeof(int) * 2 * num_pipe)))
	{
		ft_putstr_fd("malloc Erorr\n", 1);
		return (NULL);
	}
	while (++i < num_pipe)
	{
		if (pipe(fds + i * 2) < 0)
		{
			ft_putstr_fd("pipe Error\n", 1);
			return (NULL);
		}
	}
	return (fds);
}

void			save_fds(int *fds)
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
}

void	restore_fds(int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	dup2(fds[2], 2);
	close(fds[2]);
}

void	close_pipes(int *fds, int num_pipe)
{
	int		i;

	i = 0;
	while (i < 2 * num_pipe)
		close(fds[i++]);
}

int		wait_child(t_cmds *cmds, pid_t pid)
{
	int i;
	int status;

	i = -1;
	if (!cmds->num_pipe)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		while (++i < cmds->num_pipe + 1)
		{
			// puts("hhhhh");
			waitpid(cmds->pipe.pids[i], &status, 0);
			//if (status)
		}
	}
	return (status);
}

void	get_cmd_help(t_cmds *cmds, t_cmd_list *list, pid_t pid)
{
	int status;
	int shift;

	status = 0;
	close_pipes(cmds->pipe.fds, cmds->num_pipe);
	status = wait_child(cmds, pid);
	// puts("waaa akhdeeeem");
	if (cmds->num_pipe)
	{
		free(cmds->pipe.fds);
		free(cmds->pipe.pids);
	}
}

int		is_builtin(char *cmd)
{
	if (cmd && ft_strcmp(cmd, "env") && ft_strcmp(cmd, "cd") &&
		ft_strcmp(cmd, "pwd") && ft_strcmp(cmd, "exit") &&
		ft_strcmp(cmd, "export") && ft_strcmp(cmd, "unset") &&
		ft_strcmp(cmd, "echo"))
		return (0);
	return (1);
}

void			check_file(char *file, int cas, t_cmds *cmds, t_cmd_list *list)
{
	struct stat	file_stat;

	if (cas == 1)
	{
		if (stat(file, &file_stat) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(list->args[0], 1);
			ft_putstr_fd(": ", 1);
			ft_putendl_fd(strerror(errno), 1);
			return ;
		}
		if (!ft_access(file, 1))
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(list->args[0], 1);
			ft_putendl_fd(": Permission denied", 1);
			return ;
		}
		if (stat(file, &file_stat) == 0)
		{
			puts("am here again");
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(list->args[0], 1);
			ft_putendl_fd(": is a directory", 1);
			return ;
		}

	}
	else if (cas == 2)
	{
		stat(file, &file_stat);
		if (file_stat.st_mode == 16877)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(list->args[0], 1);
			ft_putendl_fd(": is a directory", 1);
		}
		if (stat(file, &file_stat) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(list->args[0], 1);
			ft_putstr_fd(": ", 1);
			ft_putendl_fd(strerror(errno), 1);
		}
	}
}

void		check_cmd(t_cmds *cmds, t_cmd_list *list)
{
	int ret = 0;
	char *path;

	if ((list->args[0][0] == '.' && list->args[0][1] == '/')
	|| (list->args[0][0] == '.' && list->args[0][1] == '.' && list->args[0][2] == '/')
	|| (ft_strchr(list->args[0], '/')))
	{
		if (list->args[0][ft_strlen(list->args[0]) - 1] == '/')
		{
			check_file(list->args[0], 2, cmds, list);
		}
		else
		{
			check_file(list->args[0], 1, cmds, list);
		}
		//execve(list->args[0], list->args, cmds->envir);
	}
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
		}
	}
}

static t_cmd_list *skip_append(t_cmd_list *list)
{
	while (list && list->redir > 0)
	{
		if (!list->next)
			break ;
		list = list->next;
	}
	return (list);
}

int		get_num_pipes(t_cmd_list *cmds)
{
	int i;

	i = 0;
	while (cmds->next)
	{
		if (cmds->end)
			break ;
		if (!cmds->redir)
			i++;
		cmds = cmds->next;	
	}
	return (i);
}

t_cmd_list	*skip_redir(t_cmd_list *cmds)
{
	while (cmds && cmds->redir)
		cmds = cmds->next;
	return (cmds);
}

t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	//char *path;
	//int ret = 0;
	pid_t pid;
	// while (head)
	// {
		///////////////////////////////////////////////////
	head->args = split_cmd(head->data, ' ', cmds);
	// puts(head->data);
	// printf("%d\n", cmds->num_pipe);
	cmds->num_pipe = get_num_pipes(head);
	// printf("%d\n", cmds->num_pipe);
	cmds->pipe.file_num = 0;
	if (cmds->num_pipe)
		cmds->pipe.pids = malloc(sizeof(int) * (cmds->num_pipe + 1));
	//head = excute_command_by_order(cmds, cmds);
	// printf("0|%s|\n", head->args[0]);
	// printf("1|%s|\n", head->args[1]);
	// printf("2|%s|\n", head->args[2]);
	// printf("3|%s|\n", head->args[3]);
	
	if ((head->next && !head->end) || !is_builtin(head->args[0]))
	{
		cmds->pipe.fds = pipe_fds(cmds->num_pipe, cmds->pipe.fds); //pipe_fds(cmds->num_pipe, cmds->pipe.fds)
		// printf("%d %d\n", cmds->pipe.fds[0] , cmds->pipe.fds[1]);
		save_fds(cmds->pipe.backup);
		cmds->pipe.file_num = 0;
		while (head)
		{
			head->args = split_cmd(head->data, ' ', cmds);
			// puts(head->args[1]);
			//printf("head->data ==> |%s|\n", head->data);
			//if (cmds->num_pipe)
			//{
			//if (head->redir)
			//{
				// puts("jj");
				pid = exec_child(cmds, head);
				//head = skip_append(head);
				head = skip_redir(head);

				cmds->pipe.file_num += 2;
					
			//}
			//}
			if (head->end)
				break ;
			// else
				head = head->next;
		}
		restore_fds(cmds->pipe.backup);
		get_cmd_help(cmds, head, pid);
			//close_fds(cmds->pipe.fds, cmds->num_pipe);
			//close_fds(cmds->pipe.fds, 1);
	}
	else if (head->args[0])
	{
		///////////////////////////////////////////////////
		if (ft_strcmp(head->args[0], "cd") == 0)
		{
			cmd_cd(head, cmds);
		}
		else if (ft_strcmp(head->args[0], "pwd") == 0)
			cmd_pwd(cmds);
		else if (ft_strcmp(head->args[0], "export") == 0)
			cmd_export(head, cmds);
		else if (ft_strcmp(head->args[0], "unset") == 0)
			cmd_unset(head, cmds);
		else if (ft_strcmp(head->args[0], "exit") == 0)
			cmd_exit();
		else if (ft_strcmp(head->args[0], "echo") == 0)
		{
			cmd_echo(head);
		}
		else if (ft_strcmp(head->args[0], "env") == 0)
			cmd_env(cmds, head);
		// else
		// {
		// 	check_cmd(cmds, head);
		// }
	}
	// puts(head->args[1]);
	// puts("salut");

		// if (head->end)
		// 	break ;
		// head = head->next;
	// }
	return head;
}

void	free_cmd_list(t_cmds *cmds)
{
	t_cmd_list *tmp;

	if (cmds->cmd_list)
	{
		while (cmds->cmd_list)
		{
			tmp = cmds->cmd_list->next;
			free(cmds->cmd_list);
			cmds->cmd_list = tmp;
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
    t_cmds		*cmds;
    t_cmd_list	*list;
    char		*line;
    int			status;
	int			i;

    cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd_list = NULL;
	cmds->index = 0;
	cmds->oldpwd = NULL;
	cmds->cd = 0;
	cmds->minus = 0;
    cmds->envir = envp;
	cmds->index = 0;
	cmds->oldpwd = NULL;
	cmds->save_oldpwd = NULL;
	cmds->cd = 0;
	cmds->minus = 0;
    cmds->env_val = NULL;
    cmds->env_arg = NULL;
	cmds->quote = 0;
	cmds->ignore = 0;
	ft_putstr_fd("\e[1;31mminishell~>\e[0m", 1);
    while ((status = get_next_line(0, &line)) > 0)
    {
        if (ft_strcmp(line, ""))
        {
        	parse_line(&line, cmds);
        	if (cmds->cmd_list)
			{
				list = cmds->cmd_list;
				while (list)
				{
					// printf("***** LINE %s\n", list->line);
					if (!list->line)
						break ;
					parse_list_line(&list->line, list, cmds);
					list = get_cmd(cmds, list);
					// puts(list->data);
					// if (list->end)
					// 	break ;
					if (list)
						list = list->next;
				}
            	//print_cmds(cmds->cmd_list);
				//puts("c");
				free_cmd_list(cmds);
			}
            free(line);
        }
        ft_putstr_fd("\e[1;31mminishell~>\e[0m", 1);
    }
	//free_cmds(cmds);
    return (0);
}

//	free leaks
//	manag sy err
//	$?