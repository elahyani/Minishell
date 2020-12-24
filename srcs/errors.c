/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:25:11 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:48:36 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *str, int status, t_cmds *cmds, t_cmd_list *list)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(list->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	if (status == 127)
		ft_putstr_fd(": command not found", 2);
	if (status == 200)
		status = 127;
	ft_putchar_fd('\n', 2);
	cmds->ret = status;
	exit(status);
}

int		print_error(char *cmd, char *arg, int err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 1);
	if (err == 1)
		ft_putstr_fd(": `", 2);
	else
		ft_putstr_fd(": ", 2);
	if (arg && err != 33 && err != 7)
		ft_putstr_fd(arg, 1);
	if (err == 1)
		ft_putendl_fd("': not a valid identifier", 2);
	if (err == 2)
		ft_putendl_fd(": No such file or directory", 2);
	if (err == 33)
	{
		ft_putstr_fd(arg, 1);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(err), 2);
	}
	if (err == 7)
		ft_putendl_fd(strerror(err), 2);
	return (1);
}

int		print_cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (1);
}

int		err_ret(t_cmd_list *list, t_cmds **cmds, int *r, int opt)
{
	int ret;
	int err;

	ret = 0;
	err = 0;
	if (opt == 1)
		ret = chdir(list->args[1]);
	else if (opt == 2)
		ret = chdir((*cmds)->env_line[1]);
	if (ret < 0)
	{
		*r = -1;
		err = print_cd_error(list->args[1]);
	}
	ft_free_arr((*cmds)->env_line);
	return (err);
}
