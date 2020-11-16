/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:57:57 by elahyani          #+#    #+#             */
/*   Updated: 2019/10/30 18:31:23 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	len;
	unsigned int	j;

	if (!src)
		return (0);
	len = ft_strlen(src);
	if (!size)
		return (len);
	j = 0;
	while (*src && j < size - 1)
	{
		*dst = *src;
		dst++;
		src++;
		j++;
	}
	*dst = '\0';
	return (len);
}
