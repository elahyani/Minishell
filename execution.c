/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:14:42 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/17 13:30:38 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	get_env(t_cmds *cmds)
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
} */

/* void	cmd_cd(t_cmd_list *list, t_cmds *cmds)
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
	get_env(cmds);
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
	}
	else if (list->args[1][0] != '~' && list->args[1][0] != '-' &&
		list->args[1][0] != '/' && list->args[1][0] != 92)
	{
		// if (list->args[1][0] == '/')
		// {
		// 	ft_putstr_fd("minishell: cd: " , 1);
		// 	ft_putstr_fd(list->args[1], 1);
		// 	ft_putstr_fd(" :: No such file or directory", 1);
		// }
		//printf("path = |%s|\n", list->args[1]);
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
		// i = 0;
		// int c = 0;
		// while (list->args[1][i] == 92)
		// {
		// 	if (c % 2 != 0)
		// 	{
		// 		list->args[1] = list->args[1] + 1;
		// 		i++;
		// 	}
		// 	c++;
		// }
		printf("path = |%s|\n", list->args[1]);
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
		puts("else\n");
		printf("path = |%s|\n", list->args[1]);
		ft_putendl_fd("No such file or directory", 1);
	}
	cmds->pwd = getcwd(NULL, 0);
	cmds->envir = ft_setenv("PWD", cmds->pwd, cmds->envir);
	cmds->envir = ft_setenv("OLDPWD", cmds->save_oldpwd, cmds->envir);
	if (ret_old == 0)
		ft_putendl_fd(cmds->pwd, 1);
}
 */
/* void	cmd_env(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		if (ft_strchr(cmds->envir[i], '='))
			ft_putendl_fd(cmds->envir[i], 1);
		i++;
	}
	///////////Ajoute PWD a env//////////////////
	// cmds->pwd = getcwd(NULL, 0);
	// if (cmds->pwd)
	// {
	// 	while (cmds->envir[j] != NULL)
	// 	{
	// 		cmds->env_line = ft_split(cmds->envir[j], '=');
	// 		if (ft_strcmp(cmds->env_line[0], "PWD") == 0)
	// 		{
	// 			cmds->envir[j] = ft_strjoin("PWD=", cmds->pwd);
	// 			ft_putendl_fd(cmds->envir[j], 1);
	// 			return ;
	// 		}
	// 		j++;
	// 	}
	// 	if (cmds->envir[j] == NULL)
	// 	{
	// 		cmds->envir[j] = ft_strjoin("PWD=", cmds->pwd);
	// 		ft_putendl_fd(cmds->envir[j], 1);
	// 		cmds->envir[j + 1] = NULL; 
	// 	}
	// }
} */

/* void	cmd_pwd(t_cmds *cmds)
{
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
		ft_putendl_fd(cmds->buff, 1);
}
 */
/* void	cmd_unset(t_cmd_list *list, t_cmds *cmds)
{
	int j = 0;
	int i = 0;
	int k;
	k = 1;
	while (list->args[k] != NULL)
	{
		while (cmds->envir[j] != NULL)
		{
			cmds->env_line = ft_split(cmds->envir[j], '=');
			if (ft_strcmp(cmds->env_line[0], list->args[k]) == 0)
			{
				i = j;
				while (cmds->envir[i] != NULL)
				{
					cmds->envir[i] = cmds->envir[i + 1];
					//if (cmds->envir[i + 1] == NULL)
					//	break ;
					i++;
				}
				break ;
			}
			j++;
		}
		k++;
	}
}
 */
/* void	cmd_echo(t_cmd_list *list)
{
	int	i;
	
	i = 1;
	
	while (list->args[i])
	{
		// if (!ft_strcmp(list->args[1], "-n") && i == 1)
		// 	i++;
		ft_putstr_fd(list->args[i], 1);
		if (list->args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (ft_strcmp(list->args[1], "-n"))
		ft_putchar_fd('\n', 1);
} */

void	cmd_exit(t_cmds *cmds)
{
	ft_putstr_fd("exit\n", 1);
	free_cmd_list(cmds);
	free(cmds->line);
	free(cmds);
	exit(1);
}