/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:35:54 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:50:04 by ichejra          ###   ########.fr       */
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

void	remove_arg(t_cmds **cmds, char *arg)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while ((*cmds)->envir[j] != NULL)
	{
		(*cmds)->env_line = ft_split((*cmds)->envir[j], '=');
		if (ft_strcmp((*cmds)->env_line[0], arg) == 0)
		{
			i = j;
			while ((*cmds)->envir[i] != NULL)
			{
				(*cmds)->envir[i] = (*cmds)->envir[i + 1];
				i++;
			}
			break ;
		}
		j++;
	}
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
		remove_arg(&cmds, list->args[k]);
		k++;
	}
	return (err);
}
