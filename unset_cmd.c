/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:35:54 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/01 14:35:21 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///////////////////////////////////////////////////////////

/* int		print_error(char *str, int err, int iscmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (err == 2 && iscmd)
		ft_putstr_fd(": command not found", 2);
	else if (err)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(err), 2);
	}
	ft_putchar_fd('\n', 2);
	return (1);
} */

////////////////////////////////////////////////////////

int		ft_isalnum_str(char *str)
{
	int i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '=' || str[i] == '_')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int		valid_arg_name(char *val)
{
	if (ft_isdigit(val[0]) || ft_strchr(val, ' ') || !ft_isalnum_str(val))
		return (0);
	return (1);
}

void	cmd_unset(t_cmd_list *list, t_cmds *cmds)
{
	int j = 0;
	int i = 0;
	int k;
	k = 1;
	while (list->args[k] != NULL)
	{
		while (cmds->envir[j] != NULL)
		{
			if (!valid_arg_name(list->args[k]) || ft_strchr(list->args[k], '='))
			{
				ft_putstr_fd("minishell: unset: `", 1);
				ft_putstr_fd(list->args[k], 1);
				ft_putendl_fd("': not a valid identifier", 1);
				return ;
			}
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
