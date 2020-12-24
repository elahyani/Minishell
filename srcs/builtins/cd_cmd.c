/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:30:08 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:49:49 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		cd_tilda(t_cmd_list *list, t_cmds **cmds)
{
	int	i;
	int err;

	i = 0;
	err = 0;
	if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		err = err_ret(list, cmds, 0, 2);
	else if (list->args[1][1] == '/')
	{
		list->args[1] = ft_strjoin((*cmds)->env_line[1], list->args[1] + 1);
		err = err_ret(list, cmds, 0, 1);
	}
	else if (list->args[1][1] == '-')
	{
		i = ft_getenv("OLDPWD", (*cmds)->envir);
		if (i == -1 && (err = 2))
			ft_putendl_fd("minishell: cd: ~-: No such file or directory", 1);
		else
		{
			(*cmds)->ret_old = chdir((*cmds)->envir[i] + 7);
			((*cmds)->ret_old < 0) ? err = print_cd_error(list->args[1]) : 0;
		}
	}
	return (err);
}

void	ft_set_path(t_cmd_list *list, t_cmds **cmds, int *ret)
{
	(*cmds)->pwd = getcwd(NULL, 0);
	(*cmds)->envir = ft_setenv("PWD", (*cmds)->pwd, (*cmds)->envir);
	if (*ret != -1)
	{
		(*cmds)->envir = ft_setenv("OLDPWD", (*cmds)->oldpwd, (*cmds)->envir);
		(*cmds)->allocated = 1;
	}
	if ((*cmds)->ret_old == 0)
	{
		if (list->args[1][0] == '-')
			ft_putendl_fd((*cmds)->pwd, 1);
	}
}

int		cd_minus(t_cmds **cmds, t_cmd_list *list)
{
	int		err;
	int		i;

	err = 0;
	if ((i = ft_getenv("OLDPWD", (*cmds)->envir)) == -1)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
		err = 3;
	}
	else
	{
		(*cmds)->ret_old = chdir((*cmds)->envir[i] + 7);
		if ((*cmds)->ret_old < 0)
			err = print_cd_error(list->args[1]);
	}
	return (err);
}

int		implement_cd(t_cmds **cmds, t_cmd_list *list, int *ret, int *err)
{
	if (list->args[1] == NULL)
		*err = err_ret(list, cmds, ret, 2);
	else if (!ft_strcmp(list->args[1], "\0") && ((*cmds)->is_ret = 1))
		return (0);
	else if (list->args[1][0] == '-')
	{
		if (((*err = cd_minus(cmds, list)) == 3))
			return ((*cmds)->is_ret = 1);
	}
	else if (list->args[1][0] == '~')
	{
		if ((*err = cd_tilda(list, cmds)) == 2)
			return ((*cmds)->is_ret = 1);
	}
	else if (list->args[1][0] == '/' && list->args[1][1] == '/' &&
	list->args[1][2] == '\0')
		*err = err_ret(list, cmds, ret, 1);
	else if ((list->args[1][0] == '/' && list->args[1][1] == '\0') || (list->
	args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '/'))
		*err = err_ret(list, cmds, ret, 1);
	else if (list->args[1][0] == 92 && list->args[1][1] == 92)
		*err = err_ret(list, cmds, ret, 1);
	else
		*err = err_ret(list, cmds, ret, 1);
	return (*err);
}

int		cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int		ret;
	int		err;

	err = 0;
	ret = 0;
	cmds->is_ret = 0;
	cmds->ret_old = 1;
	cmds->oldpwd = getcwd(NULL, 0);
	get_home_env(cmds);
	err = implement_cd(&cmds, list, &ret, &err);
	if (!cmds->is_ret)
		ft_set_path(list, &cmds, &ret);
	return (err);
}
