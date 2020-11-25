/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tris.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:15:06 by ichejra           #+#    #+#             */
/*   Updated: 2020/11/25 12:35:27 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**tri_selection(char  **envr, int n)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	k = 0;
	while (envr[i])
	{
		j = i + 1;
		while (envr[j])
		{
			while (envr[i][k] == envr[j][k])
				k++;
			if (envr[i][k] == envr[j][k])
			{
				tmp = envr[i];
				envr[i] = envr[j];
				envr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envr);
}