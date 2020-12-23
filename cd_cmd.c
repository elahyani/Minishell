/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:30:08 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/23 12:28:09 by elahyani         ###   ########.fr       */
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
		ft_free_arr(cmds->env_line);
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


int err_ret(t_cmd_list *list, t_cmds *cmds, int opt)
{
	int ret;
	int err;
	
	ret = 0;
	err = 0;
	if (opt == 1)
		ret = chdir(list->args[1]);
	else if (opt == 2)
		ret = chdir(cmds->env_line[1]);
	if (ret < 0)
		err = print_cd_error(list->args[1]);
	ft_free_arr(cmds->env_line);
	return(err);
}

int		cd_tilda(t_cmd_list *list, t_cmds *cmds, int *ret_old, int *i)
{
	int err;

	err = 0;
	puts("am in");
	if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
	{
		err = err_ret(list, cmds, 2);
		// ret = chdir(cmds->env_line[1]);
		// if (ret < 0)
		// 	err = print_cd_error(list->args[1]);
	}
	else if (list->args[1][1] == '/')
	{
		list->args[1] = ft_strjoin(cmds->env_line[1], list->args[1] + 1);
		err = err_ret(list, cmds, 1);
	}
	else if (list->args[1][1] == '-')
	{
		if ((*i = ft_getenv("OLDPWD", cmds->envir)) == -1)
		{
			ft_putendl_fd("minishell: cd: ~-: No such file or directory", 1);
			err = 2;
			//return (1);
		}
		else
		{
			*ret_old = chdir(cmds->envir[*i] + 7);
			if (ret_old < 0)
				err = print_cd_error(list->args[1]);
		}
	}
	return (err);
}


int	cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int		i;
	int		ret_old;
	int		ret;
	//int		c;
	int err;

	ret_old = 1;
	err = 0;
	ret = 0;
	i = 0;
	// cmds->allocated = 0;
	//c = 0;
	cmds->oldpwd = getcwd(NULL, 0);
	get_home_env(cmds);
	if (list->args[1] == NULL)
	{
		err = err_ret(list, cmds, 2);
		// ret = chdir(cmds->env_line[1]);
		// if (ret < 0)
		// 	err = print_cd_error(list->args[1]);
	}
	else if (!ft_strcmp(list->args[1], "\0"))
	{
		return (0);
	}
	else if (list->args[1][0] == '-')
	{
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
		err = cd_tilda(list, cmds, &ret_old, &i);
		if (err == 2)
			return (1);
		// puts("hhhh");
		// if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		// {
		// 	err = err_ret(list, cmds, 2);
		// 	// ret = chdir(cmds->env_line[1]);
		// 	// if (ret < 0)
		// 	// 	err = print_cd_error(list->args[1]);
		// }
		// else if (list->args[1][1] == '/')
		// {
		// 	list->args[1] = ft_strjoin(cmds->env_line[1], list->args[1] + 1);
		// 	err = err_ret(list, cmds, 1);
		// }
		// else if (list->args[1][1] == '-')
		// {
		// 	if ((i = ft_getenv("OLDPWD", cmds->envir)) == -1)
		// 	{
		// 		ft_putendl_fd("minishell: cd: ~-: No such file or directory", 2);
		// 		return (1);
		// 	}
		// 	else
		// 	{
		// 		ret_old = chdir(cmds->envir[i] + 7);
		// 		if (ret_old < 0)
		// 			err = print_cd_error(list->args[1]);
		// 	}
		// }
	}
	else if (list->args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '\0')
		err = err_ret(list, cmds, 1);
	else if ((list->args[1][0] == '/' && list->args[1][1] == '\0') ||
		(list->args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '/'))
		err = err_ret(list, cmds, 1);
	else if (list->args[1][0] != '~' && list->args[1][0] != '-' &&
		list->args[1][0] != '/' && list->args[1][0] != 92)
		err = err_ret(list, cmds, 1);
	else if (list->args[1][0] == 92 && list->args[1][1] == 92)
		err = err_ret(list, cmds, 1);
	else
	{
		ret = -1;
		err = print_cd_error(list->args[1]);
	}
	cmds->pwd = getcwd(NULL, 0);
	cmds->envir = ft_setenv("PWD", cmds->pwd, cmds->envir);
	if (ret != -1)
	{
		cmds->envir = ft_setenv("OLDPWD", cmds->oldpwd, cmds->envir);
		cmds->allocated = 1;
	}
	if (ret_old == 0)
	{
		if (list->args[1][0] == '-')
			ft_putendl_fd(cmds->pwd, 1);
	}
	return (err);
}
