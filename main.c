	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/07 12:17:38 by elahyani         ###   ########.fr       */
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

char	*try_path(char *filename, char *dir)
{
	char	*path;
	int		len;

	len = ft_strlen(filename) + ft_strlen(dir) + 2;
	if (!(path = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, filename);
	if (ft_access(path, 1) == 1)
		return (path);
	//ft_del(path);
	return (NULL);
}


char	*get_bin_path(char *filename, char **env)
{
	char	*path;
	int		i;
	char	**a_path;
	char	*b_path;

	path = NULL;
	a_path = NULL;
	i = 0;
	if ((i = ft_getenv("PATH", env)) >= 0)
		path = env[i] + 5;
	if (path && (a_path = ft_split(path, ':')))
	{
		i = 0;
		while (a_path[i])
		{
			if ((b_path = try_path(filename, a_path[i])))
			{
				//ft_free_arr(a_path);
				return (b_path);
			}
			i++;
		}
	}
	//ft_free_arr(a_path);
	return (filename);
}


////////////////////////////////////////////


t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	char *path;
	int ret = 0;
	// char* argv[] = { "ls", NULL };
	// char *env_args[] = {"PATH=/bin", (char*)0};
	while (head)
	{
		head->args = ft_split(head->data, ' ');
		if (ft_strcmp(head->args[0], "cd") == 0)
			cmd_cd(head, cmds);
		else if (ft_strcmp(head->args[0], "pwd") == 0)
			cmd_pwd(cmds);
		else if (ft_strcmp(head->args[0], "export") == 0)
			cmd_export(head, cmds);
		else if (ft_strcmp(head->args[0], "unset") == 0)
			cmd_unset(head, cmds);
		else if (ft_strcmp(head->args[0], "exit") == 0)
			cmd_exit();
		else if (ft_strcmp(head->args[0], "echo") == 0)
			cmd_echo(head);
		else if (ft_strcmp(head->args[0], "env") == 0)
			cmd_env(cmds, head);
		else
		{
			path = get_bin_path(head->args[0], cmds->envir);
			ret = execve(path, head->args, cmds->envir);
			//printf("\npat=|%d|\n", ret);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: ", 1);
				ft_putstr_fd(head->args[0], 1);
				ft_putendl_fd(": command not found", 1);
			}
		}
		// else
		// 	execve("/bin/ls", argv, env_args);
		// else   
		// 	execve(head->args[0], head->args, cmds->envir);
		if (head->end)
			break ;
		head = head->next;
	}
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
    // list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
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
    // list->line = NULL;
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
					//printf("***** LINE %s\n", list->line);
					if (!list->line)
						break ;
					parse_list_line(&list->line, list, cmds);
					list = get_cmd(cmds, list);
					list = list->next;
				}
            	print_cmds(cmds->cmd_list);
				free_cmd_list(cmds);
			}
            free(line);
        }
        ft_putstr_fd("\e[1;31mminishell~>\e[0m", 1);
    }
	// free cmds
    return (0);
}
