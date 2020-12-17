/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:14:42 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/17 14:23:48 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* int		print_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (1);
} */


int	cmd_exit(t_cmds *cmds)
{
	ft_putstr_fd("exit\n", 1);
	free_cmd_list(cmds);
	free(cmds->line);
	free(cmds);
	exit(1);
	return (0);
}