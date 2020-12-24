/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:28:14 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:48:34 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				check_access(char *path, int mode)
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

char			*check_path(char *cmd, char *dir)
{
	char		*path;
	int			len;

	len = ft_strlen(cmd) + ft_strlen(dir) + 2;
	if (!(path = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	if (check_access(path, 1) == 1)
		return (path);
	free(path);
	return (NULL);
}

char			*get_bin_path(char *cmdfile, char **env)
{
	char		*path;
	int			i;
	char		**split_path;
	char		*acc_path;

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
			if ((acc_path = check_path(cmdfile, split_path[i])))
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

void			check_file(char *file, int cas, t_cmds *cmds, t_cmd_list *list)
{
	struct stat	file_stat;

	if (cas == 1)
	{
		if (stat(file, &file_stat) < 0)
			exit_error(strerror(errno), 200, cmds, list);
		if (!check_access(file, 1))
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
			exit_error(strerror(errno), 1, cmds, list);
	}
}

void			check_cmd(t_cmds *cmds, t_cmd_list *list)
{
	int			ret;
	char		*path;

	ret = 0;
	if ((list->args[0][0] == '.' && list->args[0][1] == '/') ||
		(ft_strchr(list->args[0], '/')))
	{
		(list->args[0][ft_strlen(list->args[0]) - 1] == '/') ?
			check_file(list->args[0], 2, cmds, list) :
			check_file(list->args[0], 1, cmds, list);
		execve(list->args[0], list->args, cmds->envir);
	}
	else if (list->args[0][0] == '<' || list->args[0][0] == '>')
		return ;
	else
	{
		path = get_bin_path(list->args[0], cmds->envir);
		if ((ret = execve(path, list->args, cmds->envir)) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(list->args[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
}
