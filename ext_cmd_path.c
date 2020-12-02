/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:39:13 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/02 11:54:09 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int		ft_getenv(char *name, char **env)
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
			//ft_del(search);
			//ft_del(tmp);
			return (i);
		}
		//ft_del(tmp);
		i++;
	}
	//ft_del(search);
	return (-1);
} */

int		ft_access(char *path, int mode)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) < 0)
		return (0);
	if (mode == 1)
		return (file_stat.st_mode & S_IXUSR ? 1 : 0);
	else if (mode == 2)
		return (file_stat.st_mode & S_IWUSR ? 1 : 0);
	else if (mode == 4)
		return (file_stat.st_mode & S_IRUSR ? 1 : 0);
	return (0);
}

char	*try_path(char *filename, char *dir)
{
	char	*path;
	int		len;

	len = ft_strlen(filename) + ft_strlen(dir) + 2;
	if (!(path = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, filename);
	if (ft_access(path, 1) == 1)
		return (path);
	//ft_del(path);
	return (NULL);
}

char	*get_bin_path(char *filename, char **env)
{
	char	*path;
	int		i;
	char	**a_path;
	char	*b_path;

	path = NULL;
	a_path = NULL;
	i = 0;
	if ((i = ft_getenv("PATH", env)) >= 0)
		path = env[i] + 5;
	if (path && (a_path = ft_split(path, ':')))
	{
		i = 0;
		while (a_path[i])
		{
			if ((b_path = try_path(filename, a_path[i])))
			{
				//ft_free_arr(a_path);
				return (b_path);
			}
			i++;
		}
	}
	//ft_free_arr(a_path);
	return (filename);
}
