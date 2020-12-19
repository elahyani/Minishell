/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/19 13:44:00 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


////////////////////////////////////////////

void	ft_free_arr(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		ft_free_str(str[i]);
	free(str);
}

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
				ft_free_arr(split_path);
				return (acc_path);
			}
			i++;
		}
	}
	ft_free_arr(split_path);
	return (cmdfile);
}

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
			waitpid(cmds->pipe.pids[i], &status, 0);
			if (status == 2)
				if (i != cmds->num_pipe)
					cmds->sig = 1;
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
			exit_error(strerror(errno), 200, cmds, list);
		if (!ft_access(file, 1))
			exit_error("Permission denied", 126, cmds, list);
		if (file_stat.st_mode == 16877)
			exit_error("is a directory", 126, cmds, list);

	}
	else if (cas == 2)
	{
		stat(file, &file_stat);
		if (file_stat.st_mode == 16877)
			exit_error("is a directory", 126, cmds, list);
		if (stat(file, &file_stat) < 0)
			exit_error(strerror(errno), 1 , cmds, list);
	}
}

void 		check_cmd(t_cmds *cmds, t_cmd_list *list)
{
	int ret;
	char *path;

	ret = 0;
	// if ((list->args[0][0] == '.' && list->args[0][1] == '/')
	// || (list->args[0][0] == '.' && list->args[0][1] == '.' && list->args[0][2] == '/')
	// || (ft_strchr(list->args[0], '/')))
	if ((list->args[0][0] == '.' && list->args[0][1] == '/') ||
		(ft_strchr(list->args[0], '/')))
	{
		if (list->args[0][ft_strlen(list->args[0]) - 1] == '/')
			check_file(list->args[0], 2, cmds, list);
		else
			check_file(list->args[0], 1, cmds, list);
		execve(list->args[0], list->args, cmds->envir);
	}
	else
	{
		path = get_bin_path(list->args[0], cmds->envir);
		ret = execve(path, list->args, cmds->envir);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(list->args[0], 1);
			ft_putendl_fd(": command not found", 1);
			exit(127);
		}
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

t_cmd_list	*skip_redir(t_cmd_list *list)
{
	while (list && list->redir)
		list = list->next;
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

int		exec_cmds(t_cmds *cmds, t_cmd_list *list)
{
	int ret;

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
	{
		check_cmd(cmds, list);
	}
	cmds->ret = ret;
	return (ret);
}

t_cmd_list *execute_cmd_by_order(t_cmds *cmds, t_cmd_list *list)
{
	pid_t	pid;

	if ((list->next && !list->end) || !is_builtin(list->args[0]))
	{
		cmds->pipe.fds = pipe_fds(cmds->num_pipe, cmds->pipe.fds);
		save_fds(cmds->pipe.backup);
		cmds->pipe.file_num = 0;
		while (list)
		{
			// check_cmd(cmds, list);
			pid = exec_child(cmds, list);
			//list = skip_append(list);
			list = skip_redir(list);
			cmds->pipe.file_num += 2;
			if (list->end)
				break ;
			// else
				list = list->next;
		}
		restore_fds(cmds->pipe.backup);
		get_cmd_help(cmds, list, pid);
	}
	else if (list->args[0])
	{
		cmds->ret = exec_cmds(cmds, list);
		//printf("1ret====|%d|\n", cmds->ret);
	}
	return (list);
}

t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	//char *path;
	//int ret = 0;
	//pid_t pid;
	// while (head)
	// {
		///////////////////////////////////////////////////
	cmds->num_pipe = get_num_pipes(head);
	cmds->pipe.file_num = 0;
	if (cmds->num_pipe)
		cmds->pipe.pids = malloc(sizeof(int) * (cmds->num_pipe + 1));
	head = execute_cmd_by_order(cmds, head);
		// if (head->end)
		// 	break ;
		// head = head->next;
	// }
	return head;
}

void	free_cmd_list(t_cmds *cmds)
{
	int			i;
	t_cmd_list	*tmp;

	if (cmds->cmd_list)
	{
		while (cmds->cmd_list)
		{
			i = -1;
			(cmds->cmd_list->line) ? ft_free_str(cmds->cmd_list->line) : 0;
			(cmds->cmd_list->data) ? ft_free_str(cmds->cmd_list->data) : 0;
			while (cmds->cmd_list->args && cmds->cmd_list->args[++i])
				ft_free_str(cmds->cmd_list->args[i]);
			free(cmds->cmd_list->args);
			tmp = cmds->cmd_list->next;
			free(cmds->cmd_list);
			cmds->cmd_list = tmp;
		}
	}
}

void		sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		g_ret = 1;
		ft_putstr_fd("\b\b  \b\b\n", 1);
		ft_putstr_fd("\e[1;31mminishell\e[0m\033[0;33m~>\033[0m", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (g_ret == 2)
			ft_putendl_fd("Quit: 3", 2);
		else
			ft_putstr_fd("\b\b  \b\b", 2);
		//return ;
	}
}

void	initialization(t_cmds **cmds, char **envp)
{
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	(*cmds)->cmd_list = NULL;
	(*cmds)->index = 0;
	(*cmds)->cd = 0;
	(*cmds)->minus = 0;
    (*cmds)->envir = envp;
	(*cmds)->oldpwd = NULL;
	(*cmds)->save_oldpwd = NULL;
    (*cmds)->env_val = NULL;
    (*cmds)->env_arg = NULL;
	(*cmds)->quote = 0;
	(*cmds)->ignore = 0;
	(*cmds)->ret = 0;
	(*cmds)->sig = 0;
}

int		main(int argc, char **argv, char **envp)
{
    int			status;
    char		*line;
    t_cmds		*cmds;
    t_cmd_list	*list;
	int			i;

	initialization(&cmds, envp);
	g_ret = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handle);
    status = 1;
    while (status)
    {
		signal(SIGQUIT, sig_handle);
		signal(SIGINT, sig_handle);
		if (cmds->ret != 130)
			ft_putstr_fd("\e[1;31mminishell~>\e[0m ", 1);
		cmds->sig = 0;
		status = get_next_line(0, &line);
		cmds->line = line;
		if (status == 0)
			cmd_exit(list, cmds);
        if (ft_strcmp(line, ""))
        {
        	parse_line(&line, cmds);
        	if (cmds->cmd_list)
			{
				g_ret = !g_ret ? 2 : g_ret;
				list = cmds->cmd_list;
				while (list)
				{
					//printf("***** LINE %s\n", list->line);
					// if (!list->line)
					// 	break ;
					parse_list_line(&list->line, list, cmds);
					list = get_cmd(cmds, list);
					list = list->next;
				}
            	// print_cmds(cmds->cmd_list);
				free_cmd_list(cmds);
			}
        }
		g_ret = 0;
		free(line);
		// if (cmds->ret != 130)
        // 	ft_putstr_fd("\e[1;31mminishell~>\e[0m", 1);
    }
    return (0);
}
