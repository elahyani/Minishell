/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:35:17 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/01 13:38:11 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(t_cmds *cmds)
{
	if ((cmds->buff = getcwd(NULL, 0)) == NULL)
	{
		//man_error();
		ft_putstr_fd("getcwd() error", 1);
	}
	else
	{
		ft_putendl_fd(cmds->buff, 1);
		//free(cmds->buff);
	}
}
