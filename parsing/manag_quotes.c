/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:04:14 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/15 09:43:54 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_quote(int c)
{
	if (c == '\"')
		return (2);
	else if (c == '\'')
		return (1);
	return (0);
}

int		quote_activer(int c, int quote)
{
	if (is_quote(c) && !quote)
		return (is_quote(c));
	else if (quote && is_quote(c) == quote)
		return (0);
	else
		return (quote);
}

char	*ft_remove_quotes(char *res)
{
	int		i;
	int		j;
	int 	quote;
	int		ignore;

	quote = 0;
	ignore = 0;
	i = 0;
	while (res[i])
	{
		j = 0;
		(res[i] == '\\' && quote != 1) ? ignore =  1 : 0;
		if (((!quote || (quote && is_quote(res[i]) == quote)) &&
		is_quote(res[i]) && !ignore))
		{
			j = i - 1;
			quote = quote_activer(res[i], quote);
			while (res[++j])
				res[j] = res[j + 1];
		}
		else if (ignore)
		{
			j = i - 1;
			while (res[++j])
				res[j] = res[j + 1];
		}
		(ignore || !j) ? i++ : 0;
		(res[i] != '\\' && ignore) ? ignore = 0 : 0;
	}
	return (res);
}
