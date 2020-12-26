/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:14:42 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/25 15:24:04 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	valid_first_arg(char *arg)
{
	int		i;

	i = -1;
	while (arg[++i] && ft_isdigit(arg[i]))
		;
	return ((arg[i] == '\0') ? 1 : 0);
}

static int	check_args_len(t_cmd_list *list)
{
	if (list && list->args)
	{
		if (ft_arr_len(list->args) > 2 && valid_first_arg(list->args[1]))
		{
			ft_putstr_fd("exit\n", 2);
			print_error("exit", list->args[1], 7);
			return (0);
		}
	}
	return (1);
}

static int	ft_nbr_len(long n)
{
	int		i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

long		valid_status(char *arg)
{
	int		i;
	int		sign;
	long	status;

	i = (arg[0] == '-' || arg[0] == '+') - 1;
	while (arg[++i] && ft_isdigit(arg[i]))
		;
	if (!arg[i])
	{
		status = ft_atoi_l(arg);
		sign = 0;
		if (arg[0] == '+' || arg[0] == '-')
			sign = 1;
		if (ft_nbr_len(status) + sign == (int)ft_strlen(arg))
			return (status);
	}
	return (255);
}

int			cmd_exit(t_cmd_list *list, t_cmds *cmds)
{
	long	status;

	status = 0;
	if (!check_args_len(list))
		return (1);
	if (list && list->args[1])
		status = valid_status(list->args[1]);
	ft_putstr_fd("exit\n", 2);
	(status > 200 && status < 300) ? print_error("exit", list->args[1], 33) : 0;
	free_cmd_list(cmds);
	cmds->envir = (cmds->envir) ? ft_free_arr(cmds->envir) : 0;
	cmds->pwd = (cmds->pwd) ? ft_free_str(cmds->pwd) : 0;
	cmds->oldpwd = (cmds->oldpwd) ? ft_free_str(cmds->oldpwd) : 0;
	free(cmds->line);
	free(cmds);
	exit(status);
}
