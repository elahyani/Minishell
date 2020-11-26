/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:37:00 by ichejra           #+#    #+#             */
/*   Updated: 2020/11/26 18:29:37 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_get_first(const char *s, int c)
{
	char	r;
	int		i;

	r = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == r)
			return (ft_substr(s, 0, i));
		else if (s[i + 1] == '\0')
			return (ft_substr(s, 0, i + 1));
		i++;
	}
	return (0);
}

static void		ft_print_export(char **arr)
{
	int		i;
	char	*tmp;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			ft_putstr_fd("decalre -x ", 1);
			tmp = ft_get_first(arr[i], '=');
			ft_putstr_fd(tmp, 1);
			free(tmp);
			if (ft_strchr(arr[i], '='))
			{
				ft_putstr_fd("=", 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(ft_strchr(arr[i], '=') + 1, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
}

static char	**ft_sort_exp(char  **envr)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = -1;
	while (envr[++i])
	{
		j = i;
		while (envr[++j])
		{
			k = 0;
			while (envr[i][k] == envr[j][k])
				k++;
			if (envr[i][k] > envr[j][k])
			{
				tmp = envr[i];
				envr[i] = envr[j];
				envr[j] = tmp;
			}
		}
	}
	return (envr);
}

void	cmd_export(t_cmd_list *list, t_cmds *cmds)
{
	int		j;
	int i = 0;
	char	**str;
	char **tmp;
	//int len;
	char	**new_env;

	//len = 0;
	if (list->args[1] == NULL)
	{
		new_env = ft_sort_exp(cmds->envir);
		ft_print_export(new_env);
		return ;
	}
	if (!cmds->index)
		while (cmds->envir[cmds->index] != NULL)
			cmds->index++;
	i = 1;
	int o;
	int c = 0;
	while (list->args[i] != NULL)
	{
		str = ft_split(list->args[i], '=');
		o = i + 1;
		c = 0;
		while (list->args[o])
		{
			if (ft_strchr(list->args[o], '='))
			{
				tmp = ft_split(list->args[o], '=');
				if (ft_strcmp(str[0], tmp[0]) == 0)
					c = o;
			}
			o++;
		}
		if (c != 0)
			list->args[i] = ft_strdup(list->args[c]);
		j = -1;
		str = ft_split(list->args[i], '=');
		while (cmds->envir[++j] != NULL && j < cmds->index)
		{
			cmds->env_line = ft_split(cmds->envir[j], '=');
			if (ft_strcmp(cmds->env_line[0], str[0]) == 0)
			{
				if (ft_strchr(cmds->envir[j], '=') && (ft_strchr(list->args[i], '=')))
				{
					free(cmds->envir[j]);
					cmds->envir[j] = ft_strdup(list->args[i]);
					puts("[[[[");
					return ;
					puts("[[[[");
				}
				else if (ft_strchr(cmds->envir[j], '=') && !(ft_strchr(list->args[i], '=')))
 				{
					return ;
				}
				else if (!ft_strchr(cmds->envir[j], '=') && !(ft_strchr(list->args[i], '=')))
				{
					return ;
				}
				else if (!ft_strchr(cmds->envir[j], '=') && (ft_strchr(list->args[i], '=')))
				{
					free(cmds->envir[j]);
					cmds->envir[j] = ft_strdup(list->args[i]);
					return ;
				}
				
			}
		}
		//printf("1---list->args[i]=|%s|\n", list->args[i]);
		//printf("2---cmds->index==|%d|\n", cmds->index);
		cmds->envir[j] = ft_strdup(list->args[i]);
		//printf("3---cmds->envir==|%s|\n", cmds->envir[cmds->index]);
		cmds->envir[j + 1] = NULL;
		cmds->index++;
		i++;
	}
}
