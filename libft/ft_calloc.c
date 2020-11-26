/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:52:39 by elahyani          #+#    #+#             */
/*   Updated: 2019/11/06 11:15:19 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (!(mem = (char *)malloc(count * size)))
		return (NULL);
	while (i < (count * size))
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
