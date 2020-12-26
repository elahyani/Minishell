/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:30:08 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/25 18:38:50 by elahyani         ###   ########.fr       */
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
	return (err);
}

int		implement_cd(t_cmds **cmds, t_cmd_list *list, int *ret, int *err)
{
	if (list->args[1] == NULL)
		*err = err_ret(list, cmds, ret, 2);
	else if (!ft_strcmp(list->args[1], "\0") && ((*cmds)->is_ret = 1))
	{
		(*cmds)->env_line = ft_free_arr((*cmds)->env_line);
		return (0);
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
	cmds->oldpwd = (cmds->oldpwd) ? ft_free_str(cmds->oldpwd) : 0;
	cmds->oldpwd = getcwd(NULL, 0);
	get_home_env(&cmds);
	err = implement_cd(&cmds, list, &ret, &err);
	if (!cmds->is_ret)
	{
		cmds->pwd = (cmds->pwd) ? ft_free_str(cmds->pwd) : 0;
		cmds->pwd = getcwd(NULL, 0);
		cmds->envir = ft_setenv("PWD", cmds->pwd, cmds->envir);
		if (ret != -1)
		{
			cmds->envir = ft_setenv("OLDPWD", cmds->oldpwd, cmds->envir);
			cmds->allocated = 1;
		}
		if (cmds->ret_old == 0)
			(list->args[1][0] == '-') ? ft_putendl_fd(cmds->pwd, 1) : 0;
	}
	return (err);
}
