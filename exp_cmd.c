/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:37:00 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/21 19:41:26 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_arr_len(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

char	**ft_envdup(char **arr)
{
	int		i;
	int		len;
	size_t	str_len;
	char	**new_arr;

	len = ft_arr_len(arr);
	if (!(new_arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str_len = (int)ft_strlen(arr[i]);
		if (!(new_arr[i] = (char *)malloc(sizeof(char) * (str_len + 1))))
			return (NULL);
		ft_strcpy(new_arr[i], arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

char	**ft_get_arr(char *value, char **arr)
{
	int		i;
	char	**new_arr;
	int		len;

	i = -1;
	new_arr = NULL;
	len = ft_arr_len(arr) + 2;
	if (!(new_arr = (char **)malloc(sizeof(char*) * len)))
		return (NULL);
	while (arr[++i] != NULL)
	{
		new_arr[i] = ft_strdup(arr[i]);
	}
	// ft_free_arr(arr);
	new_arr[i] = ft_strdup(value);
	new_arr[i + 1] = NULL;
	// ft_free_str(value);
	return (new_arr);
}

char	**ft_add_to_arr(char *value, char **arr)
{
	char	**new_arr;
	if (arr == NULL)
	{
		// ta t9elbi eliha
		if (!(new_arr = (char **)malloc(sizeof(char *) * 2)))
			return (NULL);
		new_arr[0] = value;
		new_arr[1] = NULL;
		return (new_arr);
	}
	else
		return (ft_get_arr(value, arr));
}

int		ft_getenv(char *name, char **env)
{
	char	*search;
	int		i;
	int		len;
	char	*tmp;

	search = NULL;
	len = ft_strlen(name) + 1;
	if (!(search = (char *)malloc(sizeof(char) * len)))
		return (-1);
	ft_strcpy(search, name);
	i = 0;
	while (env[i] != NULL)
	{
		tmp = ft_get_first(env[i], '=');
		if (ft_strcmp(tmp, search) == 0)
		{
			ft_free_str(search);
			ft_free_str(tmp);
			return (i);
		}
		ft_free_str(tmp);
		i++;
	}
	ft_free_str(search);
	return (-1);
}

char	**ft_setenv(char *var, char *path, char **env)
{
	int		i;
	int		len;
	char	*record;

	len = ft_strlen(var) + ft_strlen(path) + 2;
	if (!(record = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(record, var);
	ft_strcat(record, "=");
	ft_strcat(record, path);
	if ((i = ft_getenv(var, env)) >= 0)
	{
		ft_bzero(env[i], ft_strlen(env[i]));
		env[i] = ft_strdup(record);
		ft_free_str(record);
	}
	else
		return (ft_add_to_arr(record, env));
	return (env);
}

// char	**add_to_arr(char **arr, char *value, int opt)
// {
// 	int		i;
// 	int		len;
// 	char	**new_arr;

// 	len = (!opt) ? ft_arr_len(arr) + 1 : ft_arr_len(arr) + 2;
// 	if (!(new_arr = (char **)malloc(sizeof(char *) * len)))
// 		return (NULL);
// 	i = -1;
// 	while (arr[++i])
// 		new_arr[i] = ft_strdup(arr[i]);
// 	if (!opt)
// 		new_arr[i] = NULL;
// 	if (opt)
// 	{
// 		new_arr[i] = value;
// 		new_arr[i + 1] = NULL;
// 	}
// 	return (new_arr);
// }

char		*ft_get_first(const char *s, int c)
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

int	cmd_export(t_cmd_list *list, t_cmds *cmds)
{
	int		j;
	int 	i;
	int		o;
	int		c;
	int		err;
	char	**str;
	char	**tmp;
	char	**new_env;
	char	**env_sort;

	i = 0;
	err = 0;
	cmds->exp_oldp = 0;
	while (cmds->envir[i])
	{
		str = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(str[0], "OLDPWD") == 0)
			cmds->exp_oldp = 1;
		i++;
	}
	if (list->args[1] == NULL)
	{
		if (cmds->exp_oldp == 0)
		{
			cmds->envir[i] = ft_strdup("OLDPWD");
			cmds->envir[i + 1] = NULL;
		}
		env_sort = ft_envdup(cmds->envir);
		new_env = ft_sort_exp(env_sort);
		ft_print_export(new_env);
		return (0);
	}
	if (!cmds->index)
		while (cmds->envir[cmds->index] != NULL)
			cmds->index++;
	i = 1;
	while (list->args[i] != NULL)
	{
		str = ft_split(list->args[i], '=');
		if (!ft_strcmp(str[0],"_"))
		{
			i++;
			continue ;
		}
		if (!ft_isalpha(list->args[i][0]))
		{
			if (list->args[i][0] != '_')
			{
				ft_putstr_fd("minishell: export: `", 1);
				ft_putstr_fd(list->args[i], 1);
				ft_putendl_fd("': Invalid identifier", 1);
				err = 1;
			}
			
		}
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
				if ((ft_strchr(cmds->envir[j], '=') && (ft_strchr(list->args[i], '='))) || (!ft_strchr(cmds->envir[j], '=') && (ft_strchr(list->args[i], '='))))
				{
					//free(cmds->envir[j]);
					cmds->envir[j] = ft_strdup(list->args[i]);
					break ;
				}
				else if ((ft_strchr(cmds->envir[j], '=') && !(ft_strchr(list->args[i], '='))) || (!ft_strchr(cmds->envir[j], '=') && !(ft_strchr(list->args[i], '='))))
					break ;
				// else if (!ft_strchr(cmds->envir[j], '=') && !(ft_strchr(list->args[i], '=')))
				// 	break ;
				// else if (!ft_strchr(cmds->envir[j], '=') && (ft_strchr(list->args[i], '=')))
				// {
				// 	//free(cmds->envir[j]);
				// 	cmds->envir[j] = ft_strdup(list->args[i]);
				// 	break ;
				// }
			}
		}
		cmds->envir[j] = ft_strdup(list->args[i]);
		cmds->envir[j + 1] = NULL;
		cmds->index++;
		i++;
	}
	return (err);
}
