/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 09:53:09 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:49:01 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		*pipe_file_des(int num_pipe, int *fds)
{
	int	i;

	i = -1;
	if (!num_pipe)
		return (NULL);
	if (!(fds = (int *)malloc(sizeof(int) * 2 * num_pipe)))
	{
		ft_putstr_fd("malloc Erorr\n", 2);
		return (NULL);
	}
	while (++i < num_pipe)
	{
		if (pipe(fds + i * 2) < 0)
		{
			ft_putstr_fd("pipe Error\n", 2);
			return (NULL);
		}
	}
	return (fds);
}

void	save_file_des(int *fds)
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
}

int		get_num_pipes(t_cmd_list *cmds)
{
	int i;

	i = 0;
	while (cmds->next)
	{
		if (cmds->end)
			break ;
		if (!cmds->redir)
			i++;
		cmds = cmds->next;
	}
	return (i);
}

void	close_pipes(int *fds, int num_pipe)
{
	int		i;

	i = 0;
	while (i < 2 * num_pipe)
		close(fds[i++]);
}

int		*create_fds(t_cmd_list *list, int j, int *fds)
{
	if (j != 0)
	{
		if (dup2(fds[j - 2], 0) < 0)
		{
			ft_putendl_fd("Dup2 Error", 2);
			exit(1);
		}
	}
	if (list->next && !list->end && (list->p || !list->next->end))
	{
		if (dup2(fds[j + 1], 1) < 0)
		{
			ft_putendl_fd("Dup2 Error", 2);
			exit(1);
		}
	}
	return (fds);
}
