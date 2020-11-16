/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:41:48 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/06 10:53:50 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*dstr;
	const char		*sstr;
	unsigned int	i;

	dstr = (char *)dst;
	sstr = (const char *)src;
	i = 0;
	if (!dstr && !sstr)
		return (0);
	if (dst == src)
		return (dst);
	while (i < n)
	{
		dstr[i] = sstr[i];
		i++;
	}
	return (dstr);
}
