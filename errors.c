/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:25:11 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/18 11:18:25 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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