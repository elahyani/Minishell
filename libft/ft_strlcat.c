/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:32:46 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/05 10:00:11 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			s_len;
	size_t			d_len;
	size_t			len;
	unsigned int	i;

	s_len = ft_strlen(src);
	if (!dst && !size)
		return (s_len);
	d_len = ft_strlen(dst);
	len = d_len;
	i = 0;
	if (size <= d_len)
		return (s_len + size);
	else if (size > d_len)
	{
		while (src[i] && d_len < size - 1)
		{
			dst[d_len] = src[i];
			d_len++;
			i++;
		}
		dst[d_len] = '\0';
		return (s_len + len);
	}
	return (0);
}
