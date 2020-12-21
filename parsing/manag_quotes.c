/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:04:14 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/21 17:19:38 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			is_quote(int c)
{
	if (c == '\"')
		return (2);
	else if (c == '\'')
		return (1);
	return (0);
}

int			quote_activer(int c, int quote)
{
	if (is_quote(c) && !quote)
		return (is_quote(c));
	else if (quote && is_quote(c) == quote)
		return (0);
	else
		return (quote);
}

void		ig_quote(char **res, int *quote, int *i, int *j)
{
	*j = *i - 1;
	*quote = quote_activer((*res)[*i], *quote);
	while ((*res)[++*j])
		(*res)[*j] = (*res)[*j + 1];
}

void		if_ignore(char **res, int *i, int *j)
{
	*j = *i - 1;
	while ((*res)[++*j])
		(*res)[*j] = (*res)[*j + 1];
}

char		*ft_remove_quotes(char *res)
{
	int		i;
	int		j;
	int		quote;
	int		ignore;

	quote = 0;
	ignore = 0;
	i = 0;
	while (res[i])
	{
		j = 0;
		(res[i] == '\\' && quote != 1) ? ignore = 1 : 0;
		if (((!quote || (quote && is_quote(res[i]) == quote)) &&
		is_quote(res[i]) && !ignore))
			ig_quote(&res, &quote, &i, &j);
		else if (ignore)
			if_ignore(&res, &i, &j);
		(ignore || !j) ? i++ : 0;
		(res[i] != '\\' && ignore) ? ignore = 0 : 0;
	}
	res = ft_strtrim(res, "\t\v\r");
	return (res);
}
