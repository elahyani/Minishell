/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:35:17 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/24 12:50:02 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_pwd(t_cmds *cmds)
{
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	else
	{
		ft_putendl_fd(cmds->buff, 1);
		free(cmds->buff);
	}
	return (0);
}
