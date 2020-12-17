/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:34:36 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/17 13:44:20 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_check_long(long n, int sign)
{
	if (n < 0 && sign > 0)
		return (-1);
	if (n > 0 && sign < 0)
		return (0);
	return (n);
}

// int		ft_arr_len(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	if (arr)
// 	{
// 		while (arr[i] != NULL)
// 			i++;
// 	}
// 	return (i);
// }


int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int		valid_first_arg(char *arg)
{
	int		i;

	i = -1;
	while (arg[++i] && ft_isdigit(arg[i]))
		;
	return ((arg[i] == '\0') ? 1 : 0);
}

static int		check_len(t_cmd_list *list)
{
	if (list && list->args)
	{
		if (ft_arr_len(list->args) > 2 && valid_first_arg(list->args[1]))
		{
			ft_putstr_fd("exit\n", 2);
			//print_error("exit", 7, 0);
			return (0);
		}
	}
	return (1);
}

size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int		ft_nbr_len(long n)
{
	int i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static long	ft_atoi_l(const char *str)
{
	int			i;
	long long	n;
	int			sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' ||
		str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	n = n * sign;
	return (ft_check_long(n, sign));
}

long	valid_status(char *arg)
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


int cmd_exit(t_cmds *cmds, t_cmd_list *list)
{
	long status = 1;
	//int i;
	//int iscmd;
	//ft_isdigit(66);
	// status = 0;
	// if (list && list->args[1])
	// 	status = valid_status(list->args[1]);
	// // if (status > 200 && status < 300)
	// // 	print_error("exit", NULL, 33);
	// printf("status==|%ld|\n", status);
	exit(status);
	return (0);
}