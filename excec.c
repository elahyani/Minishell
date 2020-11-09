/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:17:45 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/09 10:01:55 by elahyani         ###   ########.fr       */
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

void	cmd_cd(t_cmds *cmds)
{
	int	i;

	i = 0;
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	cmds->pwd = getcwd(NULL, 0);
	get_env(cmds);
	if (cmds->args[1] == NULL)
	{
		chdir(cmds->env_line[1]);
	}
	else if (cmds->args[1] != '~' && cmds->args[1] != '-')
	{
		chdir(cmds->args[1]);
	}
	else if (cmds->args[1] == '-')
	{
		if (cmds->start == 0)
			ft_putendl_fd("bash: cd: OLDcmds-> not set", 1);
		else if (cmds->start == 1)
		{
			//chdir(cmds->oldpwd[1]);
			//printf("oldpwd: |%s|\n", cmds->oldpwd[1]);
			printf("OLDOWD\n");
		}
		printf("cmds->start 3= %d\n", cmds->start);
	}
	else if (cmds->args[1] == '~')
	{
		cmds->args[1] = ft_strjoin(cmds->env_line[1], cmds->args[1] + 1);
		chdir(cmds->args[1]);
	}
	//cmds->envir = fgt_set_env("OLDPWD", cmds->pwd, cmds->envir)
	cmds->pwd = getcwd(NULL, 0);
	cmds->envir = ft_set_env("PWD", cmds->pwd, cmds->envir);
}

void	cmd_echo(t_cmds *cmds)
{
	int	i;
	
	i = 1;
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	while (i <= cmds->counter)
	{
		ft_putstr_fd(cmds->args[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void	cmd_pwd(t_cmds *cmds)
{
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
		ft_putendl_fd(cmds->buff, 1);
}

void	cmd_env(t_cmds *cmds)
{
	printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	int	i;
	
	i = 0;
	while (cmds->envir[i] != NULL)
	{
		ft_putendl_fd(cmds->envir[i], 1);
		i++;
	}
}

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}
