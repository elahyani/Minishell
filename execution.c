/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:14:42 by ichejra           #+#    #+#             */
/*   Updated: 2020/11/18 14:04:38 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_cmds *cmds)
{
	int	i;
	
	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "HOME") == 0)
			return ;
		i++;
	}
}

char  *skip_slash(char *line)
{
	char *path;
	int		i;
	int		l;
	int 	c;
	int		j;

	c = 1;
	l = 0;
	while (line[l])
	{
		if (line[l] == '/')
			c++;
		l++;
	}
	l = l - c + 2;
	path = malloc(sizeof(char *) * (l + 1));
	i = 0;
	j = 0;
	while(line[i])
	{	
		if (line[i] == '/' && line[i + 1] == '/')
		{
			i++ ;
			continue ;
		}
		path[j] = line[i];
		i++;
		j++;
	}
	*path = *path + 1;
	if (path[2] == 92 && path[3] != 92)
	{
		i = 3;
		while (i < j)
		{
			path[i - 1] = path[i];
			if (path[i + 1] == '\0')
			{
				path[i] = '\0';
				break;
			}
			i++;
		}
	}
	/* else
	{
		i = 0;
		c = 0;
		while (path[i])
		{
			if (path[i] == '/')
				c = 0;
			if (path[i] == 92)
			{
				if (c % 2 == 0)
				{
					*path = *path + 1;
					i++;
				}
			}
			if (path[i + 1])
			c++;
		}
	} */
	/* else if (path[2] == 92)
	{
		i = 0;
		c = 0;
		while (path[i] != 92)
		{
			if (c % 2 == 0)
			{
				*path = *path + 1;
				i++;
			}
			c++;
		}
		printf("path1 = |%s|\n", path);
	} */
	printf("PATH = |%s|\n", path);
	return (path);
}

void	cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int	i;
	char *oldpwd; ////////old path
	char	*tmp;
	int ret;
	int c;
	
	ret = 0;
	i = 0;
	c = 0;
	oldpwd = "/Users";
	//cmds->pwd = getcwd(NULL, 0);
	get_env(cmds);
	if (list->args[1] == NULL)
	{
		ret = chdir(cmds->env_line[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else if (list->args[1][0] == '-')
	{
		if (oldpwd == NULL)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
		else
		{
			ret = chdir(oldpwd);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
			else
				ft_putendl_fd(oldpwd, 1);
		}
	}
	else if (list->args[1][0] == '~')
	{
		if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		{
			printf("path = |%s|\n", list->args[1]);
			ret = chdir(cmds->env_line[1]);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
		else if (list->args[1][1] == '/')
		{
			tmp = skip_slash(list->args[1]);
			list->args[1] = ft_strjoin(cmds->env_line[1], tmp + 1);
			printf("path = |%s|\n", list->args[1]);
			ret = chdir(list->args[1]);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
	}
	else if (list->args[1][0] != '~' && list->args[1][0] != '-' &&
		list->args[1][0] != '/' && list->args[1][0] != 92)
	{
		// if (list->args[1][0] == '/')
		// {
		// 	ft_putstr_fd("minishell: cd: " , 1);
		// 	ft_putstr_fd(list->args[1], 1);
		// 	ft_putstr_fd(" :: No such file or directory", 1);
		// }
		printf("path = |%s|\n", list->args[1]);
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else if (list->args[1][0] == 92)
	{
		i = 0;
		int c = 0;
		while (list->args[1][i] == 92)
		{
			if (c % 2 != 0)
			{
				list->args[1] = list->args[1] + 1;
				i++;
			}
			c++;
		}
		printf("path = |%s|\n", list->args[1]);
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else
	{
		puts("else\n");
		printf("path = |%s|\n", list->args[1]);
		ft_putendl_fd("No such file or directory", 1);
	}
	// //cmds->envir = fgt_set_env("OLDPWD", cmds->pwd, cmds->envir)
	// printf("\n1 cmd->pwd = |%s| <-------->\n", cmds->pwd);
	cmds->pwd = getcwd(NULL, 0);
	// printf("1 cmd->pwd = |%s| <-------->\n\n", cmds->pwd);
	// cmds->envir = ft_set_env("PWD", cmds->pwd, cmds->envir);
}

void	cmd_env(t_cmds *cmds)
{
	//printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	int	i;
	
	i = 0;
	while (cmds->envir[i] != NULL)
	{
		ft_putendl_fd(cmds->envir[i], 1);
		i++;
	}
}

void	cmd_pwd(t_cmds *cmds)
{
	//printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	//printf("\n1 cmd->pwd = |%s| <-------->\n\n", cmds->pwd);
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
		ft_putendl_fd(cmds->buff, 1);
}

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}