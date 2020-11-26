/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:20:16 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/07 10:23:43 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*iter;

	iter = NULL;
	if (alst == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		iter = *alst;
		while (iter->next)
			iter = iter->next;
		if (new)
		{
			iter->next = new;
			new->next = NULL;
		}
	}
}
