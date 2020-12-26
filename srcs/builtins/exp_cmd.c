/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:37:00 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/26 09:08:18 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_export_tab(t_cmds **cmds, int *j, int *i, t_cmd_list *list)
{
	while ((*cmds)->envir[++(*j)] != NULL)
	{
		(*cmds)->env_line = ft_split((*cmds)->envir[*j], '=');
		if (ft_strcmp((*cmds)->env_line[0], (*cmds)->str[0]) == 0)
		{
			(*cmds)->str = ((*cmds)->str) ? ft_free_arr((*cmds)->str) : 0;
			(*cmds)->env_line = ((*cmds)->env_line) ?
			ft_free_arr((*cmds)->env_line) : 0;
			if (((ft_strchr((*cmds)->envir[*j], '=') && (ft_strchr(
			list->args[*i], '='))) || (!ft_strchr((*cmds)->envir[*j], '=')
			&& (ft_strchr(list->args[*i], '=')))) && ((*cmds)->chk_if_eq = 1))
			{
				(*cmds)->envir[*j] = ((*cmds)->envir[*j]) ?
				ft_free_str((*cmds)->envir[*j]) : 0;
				(*cmds)->envir[*j] = ft_strdup(list->args[*i]);
				break ;
			}
			else if (((ft_strchr((*cmds)->envir[*j], '=') && !(ft_strchr(
			list->args[*i], '='))) || (!ft_strchr((*cmds)->envir[*j], '=')
			&& !(ft_strchr(list->args[*i], '=')))) && ((*cmds)->chk_if_eq = 1))
				break ;
		}
		(*cmds)->env_line = ((*cmds)->env_line) ?
		ft_free_arr((*cmds)->env_line) : 0;
	}
}

int		print_export_list(t_cmds *cmds, int *i)
{
	i = 0;
	cmds->env_sort = ft_envdup(cmds->envir);
	cmds->new_env = ft_sort_exp(cmds->env_sort);
	ft_print_export(cmds->new_env);
	cmds->new_env = ft_free_arr(cmds->new_env);
	return (0);
}

void	add_to_export_list(t_cmds **cmds, t_cmd_list *list, int *i, int *j)
{
	(*cmds)->chk_if_eq = 0;
	(*cmds)->str = ((*cmds)->str) ? ft_free_arr((*cmds)->str) : 0;
	(*cmds)->str = ft_split(list->args[*i], '=');
	update_export_tab(&(*cmds), j, i, list);
	(*cmds)->str = ((*cmds)->str) ? ft_free_arr((*cmds)->str) : 0;
	if (!(*cmds)->chk_if_eq)
		(*cmds)->envir = ft_get_arr(list->args[*i], (*cmds)->envir);
}

void	loop_export_list(t_cmds **cmds, t_cmd_list *list, int *i, int *j)
{
	while (list->args[*i] != NULL)
	{
		(*cmds)->str = ft_split(list->args[*i], '=');
		if (!ft_strcmp((*cmds)->str[0], "_"))
		{
			(*cmds)->str = ((*cmds)->str) ? ft_free_arr((*cmds)->str) : 0;
			(*i)++;
			continue ;
		}
		if (!ft_isalpha(list->args[*i][0]) && list->args[*i][0] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(list->args[*i], 2);
			ft_putendl_fd("': Invalid identifier", 2);
			(*cmds)->str = ((*cmds)->str) ? ft_free_arr((*cmds)->str) : 0;
			(*cmds)->exp_err = 1;
			(*i)++;
			continue;
		}
		update_dup_export(list, &(*cmds), i);
		*j = -1;
		add_to_export_list(&(*cmds), list, i, j);
		(*i)++;
	}
}

int		cmd_export(t_cmd_list *list, t_cmds *cmds)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	cmds->exp_err = 0;
	cmds->sv_pos = 0;
	cmds->srch_dup = 0;
	cmds->str = NULL;
	cmds->cmp_tab = NULL;
	cmds->env_sort = NULL;
	cmds->new_env = NULL;
	cmds->exp_oldp = 0;
	if (list->args[1] == NULL)
		return (print_export_list(cmds, &i));
	i = 1;
	loop_export_list(&cmds, list, &i, &j);
	return (cmds->exp_err);
}
