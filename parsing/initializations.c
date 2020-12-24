/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:34:50 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 12:47:19 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_stx_err(char **iscmd, t_cmds **cmds)
{
	(*cmds)->i = -1;
	(*cmds)->j = -1;
	*iscmd = NULL;
}
