/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:04:13 by elahyani          #+#    #+#             */
/*   Updated: 2019/10/26 15:26:45 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	int		i;
	char	x;

	x = (unsigned char)c;
	str = (char *)b;
	i = 0;
	while (len)
	{
		str[i] = x;
		len--;
		i++;
	}
	return (str);
}
