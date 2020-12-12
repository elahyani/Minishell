/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:30:08 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/05 12:00:14 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home_env(t_cmds *cmds)
{
	int i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "HOME") == 0)
			return ;
		i++;
	}
}

void	cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int		i;
	int		ret_old = 1;
	int		ret;
	int		c;

	ret = 0;
	i = 0;
	c = 0;
	cmds->cd++;  ///bx n9arnha m3a cd - bax t3tini l oldpwd hoa hadak
	cmds->save_oldpwd = getcwd(NULL, 0);
	cmds->oldpwd = cmds->save_oldpwd;
	cmds->pwd = getcwd(NULL, 0);
	get_home_env(cmds);
	if (list->args[1] == NULL)
	{
		ret = chdir(cmds->env_line[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else if (list->args[1][0] == '-')
	{
		cmds->minus++;
		if (cmds->minus == cmds->cd)
			cmds->oldpwd = NULL;
		if ((i = ft_getenv("OLDPWD", cmds->envir)) == -1)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
			return ;
		}
		else
		{
			ret_old = chdir(cmds->envir[i] + 7);
			if (ret_old < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
	}
	else if (list->args[1][0] == '~')
	{
		if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		{
			ret = chdir(cmds->env_line[1]);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
		else if (list->args[1][1] == '/')
		{
			list->args[1] = ft_strjoin(cmds->env_line[1], list->args[1] + 1);
			ret = chdir(list->args[1]);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
		}
		else if (list->args[1][1] == '-')
		{
			if ((i = ft_getenv("OLDPWD", cmds->envir)) == -1)
			{
				ft_putendl_fd("minishell: cd: ~-: No such file or directory", 1);
				return ;
			}
			else
			{
				ret_old = chdir(cmds->envir[i] + 7);
				if (ret_old < 0)
				{
					ft_putstr_fd("minishell: cd: ", 1);
					ft_putstr_fd(list->args[1], 1);
					ft_putstr_fd(": No such file or directory\n", 1);
				}
			}
		}
	}
	// else if ((list->args[1][1] == '/' && list->args[1][2] == '\0') || (list->args[1][1] == '/' && list->args[1][2] == '/' && list->args[1][3] == '\0'))
	else if (list->args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '\0')
	{
		ret = chdir(list->args[1]);
		// if (ret < 0)
		// {
		// 	puts("here");
		// 	ft_putstr_fd("minishell: cd: ", 1);
		// 	ft_putstr_fd(list->args[1], 1);
		// 	ft_putstr_fd(": No such file or directory\n", 1);
		// }
	}
	else if ((list->args[1][0] == '/' && list->args[1][1] == '\0') ||
		(list->args[1][0] == '/' && list->args[1][1] == '/' && list->args[1][2] == '/'))
	{
		ret = chdir(list->args[1]);
		// if (ret < 0)
		// {
		// 	puts("here");
		// 	ft_putstr_fd("minishell: cd: ", 1);
		// 	ft_putstr_fd(list->args[1], 1);
		// 	ft_putstr_fd(": No such file or directory\n", 1);
		// }
	}
	else if (list->args[1][0] != '~' && list->args[1][0] != '-' &&
		list->args[1][0] != '/' && list->args[1][0] != 92)
	{
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else if (list->args[1][0] == 92 && list->args[1][1] == 92)
	{
		//printf("path = |%s|\n", list->args[1]);
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(list->args[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	cmds->pwd = getcwd(NULL, 0);
	cmds->envir = ft_setenv("PWD", cmds->pwd, cmds->envir);
	cmds->envir = ft_setenv("OLDPWD", cmds->save_oldpwd, cmds->envir);
	if (ret_old == 0)
	{
		if (list->args[1][0] == '-')
			ft_putendl_fd(cmds->pwd, 1);
	}
}
