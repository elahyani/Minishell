/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:13:40 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/26 08:55:52 by elahyani         ###   ########.fr       */
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

char	**remove_arg(char **arr, int pos)
{
	int		i;
	int		j;
	int		len;
	char	**new_arr;

	i = 0;
	j = 0;
	new_arr = NULL;
	len = ft_arr_len(arr);
	new_arr = (char **)malloc((sizeof(char *) * len));
	while (i < len)
	{
		if (i != pos)
		{
			new_arr[j] = (char *)malloc(sizeof(char *) *
			(ft_strlen(arr[i]) + 1));
			ft_strcpy(new_arr[j], arr[i]);
			j++;
		}
		i++;
	}
	ft_free_arr(arr);
	new_arr[j] = NULL;
	return (new_arr);
}

int		cmd_unset(t_cmd_list *list, t_cmds *cmds)
{
	int i;
	int j;
	int err;

	i = 1;
	j = 0;
	err = 0;
	while (list->args[i] != NULL)
	{
		if (!valid_arg(list->args[i]) || ft_strchr(list->args[i], '='))
		{
			err = print_error(list->args[0], list->args[i], 1);
			i++;
			continue ;
		}
		if ((j = ft_getenv(list->args[i], cmds->envir)) >= 0)
			cmds->envir = remove_arg(cmds->envir, j);
		i++;
	}
	return (err);
}
