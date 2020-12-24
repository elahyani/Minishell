/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:38:47 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:48:58 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		get_home_env(t_cmds *cmds)
{
	int i;

	i = 0;
	while (cmds->envir[i] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[i], '=');
		if (ft_strcmp(cmds->env_line[0], "HOME") == 0)
			return ;
		ft_free_arr(cmds->env_line);
		i++;
	}
}

int			is_builtin(char *cmd)
{
	if (cmd && ft_strcmp(cmd, "env") && ft_strcmp(cmd, "cd") &&
		ft_strcmp(cmd, "pwd") && ft_strcmp(cmd, "exit") &&
		ft_strcmp(cmd, "export") && ft_strcmp(cmd, "unset") &&
		ft_strcmp(cmd, "echo"))
		return (0);
	return (1);
}

t_cmd_list	*skip_redir(t_cmd_list *list)
{
	while (list && list->redir)
		list = list->next;
	return (list);
}

void		create_io_fds_cpy(int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	dup2(fds[2], 2);
	close(fds[2]);
}
