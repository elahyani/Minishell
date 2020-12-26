/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:41:13 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/25 14:49:32 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_free_str(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	**ft_free_arr(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		str[i] = ft_free_str(str[i]);
	free(str);
	return (NULL);
}

void	free_cmd_list(t_cmds *cmds)
{
	int			i;
	t_cmd_list	*tmp;

	if (cmds->cmd_list)
	{
		while (cmds->cmd_list)
		{
			i = -1;
			cmds->cmd_list->line = ft_free_str(cmds->cmd_list->line);
			cmds->cmd_list->data = ft_free_str(cmds->cmd_list->data);
			while (cmds->cmd_list->args && cmds->cmd_list->args[++i])
				cmds->cmd_list->args[i] = ft_free_str(cmds->cmd_list->args[i]);
			free(cmds->cmd_list->args);
			tmp = cmds->cmd_list->next;
			free(cmds->cmd_list);
			cmds->cmd_list = tmp;
		}
	}
}
