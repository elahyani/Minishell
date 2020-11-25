/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:14:42 by ichejra           #+#    #+#             */
/*   Updated: 2020/11/25 12:41:03 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_cmds *cmds)
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
char  *skip_slash(char *line)
{
	char *path;
	int		i;
	int		l;
	int 	c;
	int		j;

	c = 1;
	l = 0;
	while (line[l])
	{
		if (line[l] == '/')
			c++;
		l++;
	}
	l = l - c + 2;
	path = malloc(sizeof(char *) * (l + 1));
	i = 0;
	j = 0;
	while(line[i])
	{	
		if (line[i] == '/' && line[i + 1] == '/')
		{
			i++ ;
			continue ;
		}
		path[j] = line[i];
		i++;
		j++;
	}
	*path = *path + 1;
	if (path[2] == 92 && path[3] != 92)
	{
		i = 3;
		while (i < j)
		{
			path[i - 1] = path[i];
			if (path[i + 1] == '\0')
			{
				path[i] = '\0';
				break;
			}
			i++;
		}
	}
	/* else
	{
		i = 0;
		c = 0;
		while (path[i])
		{
			if (path[i] == '/')
				c = 0;
			if (path[i] == 92)
			{
				if (c % 2 == 0)
				{
					*path = *path + 1;
					i++;
				}
			}
			if (path[i + 1])
			c++;
		}
	} */
	/* else if (path[2] == 92)
	{
		i = 0;
		c = 0;
		while (path[i] != 92)
		{
			if (c % 2 == 0)
			{
				*path = *path + 1;
				i++;
			}
			c++;
		}
		printf("path1 = |%s|\n", path);
	} */
	printf("PATH = |%s|\n", path);
	return (path);
}

/* char	*get_old_pwd(t_cmds *cmds)
{
	int 	i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "OLDPWD") == 0)
			return (cmds->envir[i] + 7);
		i++;
	}
	return (NULL);
}
void	set_pwd(t_cmds *cmds)
{
	int c;
	int i;
	i = 0;
	c = 0;
	while (cmds->envir[c] != NULL)
		c++;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "PWD") == 0)
			cmds->envir[i] = ft_strjoin("PWD=", cmds->pwd);
		if (ft_strcmp(cmds->env_line[0], "OLDPWD") == 0)
			cmds->envir[i] = ft_strjoin("OLDPWD=", cmds->oldpwd);
		i++;
	}
	//cmds->envir[i] = ft_strjoin("OLDPWD=", cmds->oldpwd);
} */

void	cmd_cd(t_cmd_list *list, t_cmds *cmds)
{
	int	i;
	char	*tmp;
	int ret;
	int c;
	int j = 0;
	ret = 0;
	i = 0;
	c = 0;
	cmds->cd++;  ///bx n9arnha m3a cd - bax t3tini l oldpwd hoa hadak 
	while (cmds->envir[j] != NULL)
		j++;
	cmds->oldpwd = cmds->pwd;
	cmds->pwd = getcwd(NULL, 0);
	//if (!cmds->oldpwd)
	// 	cmds->envir[j++] = ft_strjoin("OLDPWD1================", cmds->oldpwd);
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
		if (cmds->oldpwd == NULL)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
		}
		else
		{
			ret = chdir(cmds->oldpwd);
			if (ret < 0)
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(list->args[1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
			}
			else
				ft_putendl_fd(cmds->oldpwd, 1);
			cmds->envir[j] = ft_strjoin("OLDPWD1================", cmds->oldpwd);
			cmds->envir[j + 1] = NULL;
		}
	}
	else if (list->args[1][0] == '~')
	{
		if (list->args[1][1] == ' ' || list->args[1][1] == '\0')
		{
			//printf("path = |%s|\n", list->args[1]);
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
			tmp = skip_slash(list->args[1]);
			list->args[1] = ft_strjoin(cmds->env_line[1], tmp + 1);
			//printf("path = |%s|\n", list->args[1]);
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
		printf("path = |%s|\n", list->args[1]);
		ret = chdir(list->args[1]);
		if (ret < 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(list->args[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	else if (list->args[1][0] == 92)
	{
		i = 0;
		int c = 0;
		while (list->args[1][i] == 92)
		{
			if (c % 2 != 0)
			{
				list->args[1] = list->args[1] + 1;
				i++;
			}
			c++;
		}
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
	// if (cmds->pwd)
	// {
	// 	cmds->envir[j] = ft_strjoin("PWD1================", cmds->pwd);
	// 	cmds->envir[j + 1] = NULL; 
	// }	
	//if (oldpwd)
	// //cmds->envir = fgt_set_env("OLDPWD", cmds->pwd, cmds->envir)
	// printf("\n1 cmd->pwd = |%s| <-------->\n", cmds->pwd);

	//printf("cpwd2==|%s|\n", cmds->pwd);
	//if (cmds->rem != 1)
	//cmds->pwd = getcwd(NULL, 0);
	//printf("cpwd3==|%s|\n", cmds->pwd);
	// printf("1 cmd->pwd = |%s| <-------->\n\n", cmds->pwd);
	// cmds->envir = ft_set_env("PWD", cmds->pwd, cmds->envir);
	//set OLDPWD and PWD
	//set_pwd(cmds);
}

void	cmd_env(t_cmds *cmds)
{
	//printf("\ncmd = |%s| <--------> arg = |%s|\n\n", cmds->args[0], cmds->args[1]);
	int	i;
	//int j = 0;
	i = 0;
	while (cmds->envir[i] != NULL)
	{
		ft_putendl_fd(cmds->envir[i], 1);
		i++;
	}
	///////////Ajoute PWD a env//////////////////
	/* cmds->pwd = getcwd(NULL, 0);
	if (cmds->pwd)
	{
		while (cmds->envir[j] != NULL)
		{
			cmds->env_line = ft_split(cmds->envir[j], '=');
			if (ft_strcmp(cmds->env_line[0], "PWD") == 0)
			{
				cmds->envir[j] = ft_strjoin("PWD=", cmds->pwd);
				ft_putendl_fd(cmds->envir[j], 1);
				return ;
			}
			j++;
		}
		if (cmds->envir[j] == NULL)
		{
			cmds->envir[j] = ft_strjoin("PWD=", cmds->pwd);
			ft_putendl_fd(cmds->envir[j], 1);
			cmds->envir[j + 1] = NULL; 
		}
	} */
}

void	cmd_pwd(t_cmds *cmds)
{
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
		ft_putstr_fd("getcwd() error", 1);
	else
		ft_putendl_fd(cmds->buff, 1);
}

void	cmd_export(t_cmd_list *list, t_cmds *cmds)
{
	int		j;
	int i = 0;
	//int c = 0;
	char	**str;
	char **tmp;
	char **tmp2;
	int len;
	int env_len;

	env_len = 0;
	len = 0;
	j = -1;
	while (cmds->envir[env_len])
			env_len++;
	// if (cmds->exp != NULL)
	// {
	// 	printf("|0|===========|%s|\n", cmds->exp[0]);
	// 	printf("|1|===========|%s|\n", cmds->exp[1]);
	// 	printf("|2|===========|%s|\n", cmds->exp[2]);
	// }
	tmp2 = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (list->args[1] == NULL)
	{
		while (cmds->envir[i] != NULL)
		{
			tmp = ft_split(cmds->envir[i], '=');
			//printf("tmp[0]====|%s|\n", tmp[0]);
			//printf("tmp[1]====|%s|\n", tmp[1]);
			tmp2[i] = ft_strjoin("declare -x ", tmp[0]);
			tmp2[i] = ft_strjoin(tmp2[i], "=\"");
			if (tmp[1] != NULL)
				tmp2[i] = ft_strjoin(tmp2[i], tmp[1]);
			else if (tmp[1] == NULL)
				tmp2[i] = ft_strjoin(tmp2[i], "");
			tmp2[i] = ft_strjoin(tmp2[i], "\"");
			ft_putendl_fd(tmp2[i], 1);
			i++;
		}
		//int o = 0;
		/* puts("========================================");
		while (tmp2[o])
		{
			ft_putendl_fd(tmp2[o], 1);
			o++;
		} */
		puts("========================================");
		//ft_putendl_fd(cmds->envir[i], 1);
		if (cmds->exp != NULL)
		{
			i = 0;
			while (i < cmds->exp_index)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putendl_fd(cmds->exp[i], 1);
				i++;
			}
		}
		return ;
	}
	if (!cmds->index)
		while (cmds->envir[cmds->index] != NULL)
			cmds->index++;
	//list->args[1] = ft_strdup("a= ");
	//list->args[2] = ft_strdup("b");
	//printf("||=======|%s|\n", list->args[1]);
	//printf("||=======|%s|\n", list->args[2]);
	i = 1;
	while (list->args[i] != NULL)
	{
		//if (ft_strchr(list->args[i], '=') != NULL)
		str = ft_split(list->args[i], '=');
		if (list->args[i + 1] != NULL)
		{
			if (ft_strchr(list->args[i + 1], '='))
			{
				tmp = ft_split(list->args[i + 1], '=');
				if (ft_strcmp(str[0], tmp[0]) == 0)
				{
					i++;
					continue ;
				}
			}
		}
		//puts("=====3");
		//printf("str===|%s|", str[0]);
		//printf("tmp===|%s|", tmp[0]);
		//printf("|%s|\n", str[0]);
		if (ft_strchr(list->args[i], '=') != NULL)
		{
			if (ft_strchr(list->args[i], '"') == NULL)
			{
				str = ft_split(list->args[i], '=');
				//printf("str[1][0]=|%s|\n", str[0]);
				while (cmds->envir[++j] != NULL && j < cmds->index)
				{
					cmds->env_line = ft_split(cmds->envir[j], '=');
					//printf("env = |%s|\n", cmds->env_line[0]);
					if (ft_strcmp(cmds->env_line[0], str[0]) == 0)
					{
						cmds->envir[j] = ft_strdup(list->args[i]);
						return ;
					}
				}
				cmds->envir[cmds->index] = ft_strdup(list->args[i]);
				cmds->envir[j + 1] = NULL;
				cmds->index++;
			}
		}
		else if (ft_strchr(list->args[i], '=') == NULL)
		{
			while (list->args[len])
				len++;
			if (!cmds->exp)
				cmds->exp = malloc(sizeof(char *) * (len + 1));
			//printf("|%d|=======|%s|\n",cmds->exp_index, cmds->exp[cmds->exp_index]);
			cmds->exp[cmds->exp_index] = ft_strdup(list->args[i]);
			cmds->exp_index++;
		}
		i++;
	}
	//////if there is "" or ''
	// else if (ft_strchr(list->args[1], '"') != NULL)
	// {
	// 	j = 0;
	// 	while (list->args[1][j])
	// 	{
	// 		if (list->args[1][j] == '"')
	// 			c++;
	// 		j++;
	// 	}
	// 	if (c != 2)
	// 	{
	// 		ft_putendl_fd("ERROR", 1);
	// 		return ;
	// 	}
	// }
}

void	cmd_unset(t_cmd_list *list, t_cmds *cmds)
{
	int j = 0;
	int i = 0;
	int k;
	//printf("arg[1]==|%s|\n",list->args[1]);
	//printf("arg[2]==|%s|\n",list->args[2]);
	//list->args[1] = "a";
	//list->args[2] = "b";
	k = 1;
	while (list->args[k] != NULL)
	{
		//printf("|%d|", k);
		//printf("arg[%d]==|%s|\n", k, list->args[k]);
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

void	cmd_exit()
{
	ft_putstr_fd("exit\n", 1);
	exit(1);
}