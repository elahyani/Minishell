/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:43:21 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/07 10:31:26 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list		*s_lstnew;

	if (!(s_lstnew = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	s_lstnew->content = content;
	s_lstnew->next = NULL;
	return (s_lstnew);
}
