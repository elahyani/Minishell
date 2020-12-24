/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 08:50:18 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 09:05:22 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new_arr[i] = ft_strdup(value);
	new_arr[i + 1] = NULL;
	return (new_arr);
}

char	**ft_add_to_arr(char *value, char **arr)
{
	char	**new_arr;

	if (arr == NULL)
	{
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
	int		i;
	int		len;
	char	*tmp;
	char	*search;

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
			search = ft_free_str(search);
			tmp = ft_free_str(tmp);
			return (i);
		}
		tmp = ft_free_str(tmp);
		i++;
	}
	search = ft_free_str(search);
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
		record = ft_free_str(record);
	}
	else
		return (ft_add_to_arr(record, env));
	return (env);
}
