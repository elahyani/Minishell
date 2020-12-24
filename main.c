/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 12:49:21 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		g_ret = 1;
		ft_putstr_fd("\b\b  \b\b\n", 1);
		ft_putstr_fd("\e[1;31mminishell\e[0m\033[0;33m~>\033[0m ", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (g_ret == 2)
			ft_putendl_fd("Quit: 3", 2);
		else
			ft_putstr_fd("\b\b  \b\b", 2);
	}
}

void	initialization(t_cmds **cmds, char **envp, int *status, int *g_ret)
{
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	(*cmds)->cd = 0;
	(*cmds)->ret = 0;
	(*cmds)->sig = 0;
	(*cmds)->minus = 0;
	(*cmds)->quote = 0;
	(*cmds)->index = 0;
	(*cmds)->ignore = 0;
	(*cmds)->envir = envp;
	(*cmds)->allocated = 0;
	(*cmds)->oldpwd = NULL;
	(*cmds)->env_val = NULL;
	(*cmds)->env_arg = NULL;
	(*cmds)->cmd_list = NULL;
	(*cmds)->save_oldpwd = NULL;
	*status = 1;
	*g_ret = 0;
}

void	run_shell(char *line, t_cmds *cmds, t_cmd_list *list)
{
	if (ft_strcmp(line, ""))
	{
		parse_line(&line, cmds);
		if (cmds->cmd_list)
		{
			g_ret = !g_ret ? 2 : g_ret;
			list = cmds->cmd_list;
			while (list)
			{
				parse_list_line(&list->line, list, cmds);
				list = get_cmd(cmds, list);
				list = list->next;
			}
			free_cmd_list(cmds);
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	int			status;
	char		*line;
	t_cmds		*cmds;
	t_cmd_list	*list;
	int			i;

	initialization(&cmds, envp, &status, &g_ret);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handle);
	while (status)
	{
		signal(SIGQUIT, sig_handle);
		signal(SIGINT, sig_handle);
		(cmds->ret != 130) ? ft_putstr_fd("\e[1;31mminishell~>\e[0m ", 1) : 0;
		cmds->sig = 0;
		status = get_next_line(0, &line);
		cmds->line = line;
		(status == 0) ? cmd_exit(list, cmds) : 0;
		run_shell(line, cmds, list);
		g_ret = 0;
		free(line);
	}
	return (0);
}
