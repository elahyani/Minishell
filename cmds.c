/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:17:45 by elahyani          #+#    #+#             */
/*   Updated: 2020/10/27 19:58:14 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_cd(t_cmds *cmds)
{
	int	i;

	i = 0;
	printf("path: [%s]\n", cmds->cmd[0]);
	if (cmds->cmd[1][0] != '~')
		chdir(cmds->cmd[cmds->counter]);
	else if (cmds->cmd[1][0] == '~')
	{
		while (cmds->envir[i] != NULL)
		{
			if (ft_strcmp(cmds->envir[i],"HOME=/Users/elahyani") == 0)
			{
				cmds->cmd[1] = ft_strjoin(cmds->envir[i] + 5, cmds->cmd[1] + 1);
				chdir(cmds->cmd[cmds->counter]);
			}
			i++;
		}
	}
}

void	cmd_echo(t_cmds *cmds)
{
	int	i;
	
	i = 1;
	while (i <= cmds->counter)
	{
		ft_putstr_fd(cmds->cmd[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	cmd_pwd()
{
	char	*buff;

	if ((buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
	{
		buff = ft_strjoin(buff, "\n");
		ft_putstr_fd(buff, 1);
	}
	return ;
}

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}