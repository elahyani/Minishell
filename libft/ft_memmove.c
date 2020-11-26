/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:06:57 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/06 15:59:19 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ds;
	const char	*sr;
	size_t		i;

	ds = (char *)dst;
	sr = (const char *)src;
	if (!ds && !sr)
		return (0);
	i = 0;
	if (ds <= sr)
		return (ft_memcpy(ds, sr, len));
	while (len)
	{
		ds[len - 1] = sr[len - 1];
		len--;
	}
	return (ds);
}
