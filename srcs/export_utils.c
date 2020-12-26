/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 08:50:53 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/25 16:14:55 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	check_if_oldpwd(t_cmds *cmds, int *i)
{
	while (cmds->envir[*i])
	{
		if (ft_strncmp(cmds->envir[*i], "OLDPWD=", 7) == 0)
			cmds->exp_oldp = 1;
		(*i)++;
	}
}

void	ft_print_export(char **arr)
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

char	**ft_sort_exp(char **envr)
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

void	update_dup_export(t_cmd_list *list, t_cmds **cmds, int *i)
{
	(*cmds)->srch_dup = *i + 1;
	(*cmds)->sv_pos = 0;
	while (list->args[(*cmds)->srch_dup])
	{
		if (ft_strchr(list->args[(*cmds)->srch_dup], '='))
		{
			(*cmds)->cmp_tab = ft_split(list->args[(*cmds)->srch_dup], '=');
			if (ft_strcmp((*cmds)->str[0], (*cmds)->cmp_tab[0]) == 0)
				(*cmds)->sv_pos = (*cmds)->srch_dup;
			(*cmds)->cmp_tab = ((*cmds)->cmp_tab) ?
			ft_free_arr((*cmds)->cmp_tab) : 0;
		}
		((*cmds)->srch_dup)++;
	}
	if ((*cmds)->sv_pos != 0)
	{
		list->args[*i] = (list->args[*i]) ? ft_free_str(list->args[*i]) : 0;
		list->args[*i] = ft_strdup(list->args[(*cmds)->sv_pos]);
	}
}
