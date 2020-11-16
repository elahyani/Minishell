/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:02:45 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/07 10:39:58 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*s_lst;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		s_lst = list->next;
		(*del)(list->content);
		free(list);
		list = s_lst;
	}
	*lst = NULL;
}
