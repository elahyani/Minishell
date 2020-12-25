/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:35:54 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/25 19:33:20 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_isalnum_str(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '=' || str[i] == '_')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int		valid_arg(char *val)
{
	if (ft_isdigit(val[0]) || ft_strchr(val, ' ') || !ft_isalnum_str(val))
		return (0);
	return (1);
}

char		**remove_arg(t_cmds **cmds, char *arg)
{
	int		i;
	int		len;
	char	**new_arr;
	int		str_len;
	i = 0;
	len = 0;
	while ((*cmds)->envir[i] != NULL)
	{
		(*cmds)->env_line = ft_split((*cmds)->envir[i], '=');
		if (ft_strcmp((*cmds)->env_line[0], arg) == 0)
		{
			i++;
			(*cmds)->env_line = ft_free_arr((*cmds)->env_line);
			continue ;
		}
		(*cmds)->env_line = ft_free_arr((*cmds)->env_line);
		len++;
		i++;
	}
	if (!(new_arr = (char **)malloc(sizeof(char*) * (len))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		(*cmds)->env_line = ft_split((*cmds)->envir[i], '=');
		if (ft_strcmp((*cmds)->env_line[0], arg) == 0)
		{
			i++;
			(*cmds)->env_line = ft_free_arr((*cmds)->env_line);
			continue ;
		}
		(*cmds)->env_line = ft_free_arr((*cmds)->env_line);
		str_len = (int)ft_strlen((*cmds)->envir[i]);
		if (!(new_arr[i] = (char *)malloc(sizeof(char) * (str_len + 1))))
			return (NULL);
		ft_strcpy(new_arr[i], (*cmds)->envir[i]);
		i++;
	}
	new_arr[i] = NULL;
	printf("unset => %d\n", len);
	ft_free_arr((*cmds)->envir);
	return(new_arr);
}

int		cmd_unset(t_cmd_list *list, t_cmds *cmds)
{
	int	k;
	int	err;

	k = 1;
	err = 0;
	while (list->args[k] != NULL)
	{
		if (!valid_arg(list->args[k]) || ft_strchr(list->args[k], '='))
		{
			err = print_error(list->args[0], list->args[k], 1);
			k++;
			continue ;
		}
		cmds->envir = remove_arg(&cmds, list->args[k]);
		k++;
	}
	return (err);
}
