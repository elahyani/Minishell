/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:17:45 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/14 14:36:39 by elahyani         ###   ########.fr       */
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

void	cmd_cd(t_cmd_list *cmds)
{
	// int	i;
	
	// i = 0;	
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
}

void	cmd_echo(t_cmd_list *cmds)
{
	// int	i;
	
	// i = 1;
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	// while (i <= cmds->counter)
	// {
	// 	ft_putstr_fd(cmds->args[i], 1);
	// 	ft_putchar_fd(' ', 1);
	// 	i++;
	// }
	// ft_putchar_fd('\n', 1);
}

void	cmd_pwd(t_cmd_list *cmds)
{
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
}

void	cmd_env(t_cmd_list *cmds)
{
	// int	i;
	
	// i = 0;
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	// while (cmds->envir[i] != NULL)
	// {
	// 	ft_putendl_fd(cmds->envir[i], 1);
	// 	i++;
	// }
}

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}
