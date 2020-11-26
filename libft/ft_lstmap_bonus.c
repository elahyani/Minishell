/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:10:52 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/07 11:44:11 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list		*r_lst;
	t_list		*first;

	if (!lst || !f)
		return (NULL);
	if (!(r_lst = (t_list*)malloc(sizeof(r_lst))))
		return (NULL);
	first = r_lst;
	while (lst)
	{
		r_lst->content = (*f)(lst->content);
		r_lst->next = (t_list*)malloc(sizeof(r_lst));
		if (!r_lst->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		r_lst = r_lst->next;
		lst = lst->next;
	}
	return (first);
}
