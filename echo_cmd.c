/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:33:32 by ichejra           #+#    #+#             */
/*   Updated: 2020/12/12 19:29:31 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//////////////////////////////////////////////////////
/////////////////////////////////////////////////////

int			check_n_flag(char *s, int *n)
{
	int i;
	int n_flag;

	i = 0;
	n_flag = 0;
	if (s[0] == '-' && s[1] == 'n' && (s[2] == 'n' || !s[2]))
	{
		*n = 2;
		n_flag = 1;
		while (s[*n] == 'n')
			*n = *n + 1;
		if (s[*n])
		{
			*n = 0;
			n_flag = 0;
		}
	}
	return (n_flag);
}

void		print_args(char **s, int pos)
{
	if (s[pos])
		ft_putstr_fd(s[pos], 1);
	if (s[pos + 1])
		ft_putchar_fd(' ', 1);
}

void	cmd_echo(t_cmd_list *list)
{
	int	i;
	int n;
	int ret;
	
	ret = 0;
	n = 0;
	i = 1;
	//puts("bbb");
	if (!list->args[1])
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	while (list->args[i])
	{
		if (!n)
			while (list->args[i] && (ret = check_n_flag(list->args[i], &n)))
				i++;
		//if (!list->redir)
			print_args(list->args, i);
		/* if (list->prev->redir)
		{
			ft_putchar_fd('\n', 1);
			break ;
		} */
		if ((!list->args[i + 1] && !n))
			ft_putchar_fd('\n', 1);
		i++;
	}
}
