/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:30:08 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/17 12:19:20 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home_env(t_cmds *cmds)
{
	int i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "HOME") == 0)
			return ;
		i++;
	}
}

static int		print_cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (1);
}

int	cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int		i;
	int		ret_old = 1;
	int		ret;
	int		c;
	int err;

	err = 0;
	ret = 0;
	i = 0;
	c = 0;
	//cmds->cd++;  ///bx n9arnha m3a cd - bax t3tini l oldpwd hoa hadak
	//cmds->save_oldpwd = getcwd(NULL, 0);
	//cmds->oldpwd = cmds->save_oldpwd;
	cmds->oldpwd = getcwd(NULL, 0);
	
	//cmds->pwd = getcwd(NULL, 0);
	get_home_env(cmds);
	//printf("list->args====|%s|\n", list->args[1]);
	if (list->args[1] == NULL)
	{
		ret = chdir(cmds->env_line[1]);
		if (ret < 0)
			err = print_cd_error(list->args[1]);
	}
	else if (!ft_strcmp(list->args[1], "\0"))
		return (0);
	else if (list->args[1][0] == '-')
	{
		// cmds->minus++;
		// if (cmds->minus == cmds->cd)
		// 	cmds->oldpwd = NULL;
		if ((i = ft_getenv("OLDPWD", cmds->envir)) == -1)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
			return (1);
		}
		else
		{
			ret_old = chdir(cmds->envir[i] + 7);
			if (ret_old < 0)
				err = print_cd_error(list->args[1]);
		}
	}
	else if (list->args[1][0] == '~')
	{
		if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		{
			ret = chdir(cmds->env_line[1]);
			if (ret < 0)
				err = print_cd_error(list->args[1]);
		}
		else if (list->args[1][1] == '/')
		{
			list->args[1] = ft_strjoin(cmds->env_line[1], list->args[1] + 1);
			ret = chdir(list->args[1]);
			if (ret < 0)
				err = print_cd_error(list->args[1]);
		}
		else if (list->args[1][1] == '-')
		{
			if ((i = ft_getenv("OLDPWD", cmds->envir)) == -1)
			{
				ft_putendl_fd("minishell: cd: ~-: No such file or directory", 1);
				return (1);
			}
			else
			{
				ret_old = chdir(cmds->envir[i] + 7);
				if (ret_old < 0)
					err = print_cd_error(list->args[1]);
			}
		}
	}
	// else if ((list->args[1][1] == '/' && list->args[1][2] == '\0') || (list->args[1][1] == '/' && list->args[1][2] == '/' && list->args[1][3] == '\0'))
	else if (list->args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '\0')
	{
		ret = chdir(list->args[1]);
		if (ret < 0)
			err = print_cd_error(list->args[1]);
	}
	else if ((list->args[1][0] == '/' && list->args[1][1] == '\0') ||
		(list->args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '/'))
	{
		ret = chdir(list->args[1]);
		if (ret < 0)
			err = print_cd_error(list->args[1]);
	}
	else if (list->args[1][0] != '~' && list->args[1][0] != '-' &&
		list->args[1][0] != '/' && list->args[1][0] != 92)
	{
		ret = chdir(list->args[1]);
		if (ret < 0)
			err = print_cd_error(list->args[1]);
	}
	else if (list->args[1][0] == 92 && list->args[1][1] == 92)
	{
		ret = chdir(list->args[1]);
		if (ret < 0)
			err = print_cd_error(list->args[1]);
	}
	else
	{
		ret = -1;
		err = print_cd_error(list->args[1]);
	}
	cmds->pwd = getcwd(NULL, 0);
	cmds->envir = ft_setenv("PWD", cmds->pwd, cmds->envir);
	if (ret != -1)
		cmds->envir = ft_setenv("OLDPWD", cmds->oldpwd, cmds->envir);
	// kant hadi 
	// 	cmds->envir = ft_setenv("OLDPWD", cmds->save_oldpwd, cmds->envir);
	if (ret_old == 0)
	{
		if (list->args[1][0] == '-')
			ft_putendl_fd(cmds->pwd, 1);
	}
	return (err);
}
