/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichejra <ichejra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/24 11:53:19 by ichejra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arr(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i])
			ft_free_str(str[i]);
	free(str);
}

void	free_cmd_list(t_cmds *cmds)
{
	int			i;
	t_cmd_list	*tmp;

	if (cmds->cmd_list)
	{
		while (cmds->cmd_list)
		{
			i = -1;
			(cmds->cmd_list->line) ? ft_free_str(cmds->cmd_list->line) : 0;
			(cmds->cmd_list->data) ? ft_free_str(cmds->cmd_list->data) : 0;
			while (cmds->cmd_list->args && cmds->cmd_list->args[++i])
				ft_free_str(cmds->cmd_list->args[i]);
			free(cmds->cmd_list->args);
			tmp = cmds->cmd_list->next;
			free(cmds->cmd_list);
			cmds->cmd_list = tmp;
		}
	}
}

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

void	initialization(t_cmds **cmds, char **envp)
{
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	(*cmds)->cmd_list = NULL;
	(*cmds)->index = 0;
	(*cmds)->cd = 0;
	(*cmds)->minus = 0;
	(*cmds)->envir = envp;
	(*cmds)->oldpwd = NULL;
	(*cmds)->save_oldpwd = NULL;
	(*cmds)->env_val = NULL;
	(*cmds)->env_arg = NULL;
	(*cmds)->quote = 0;
	(*cmds)->ignore = 0;
	(*cmds)->ret = 0;
	(*cmds)->sig = 0;
	(*cmds)->allocated = 0;
}

int		main(int argc, char **argv, char **envp)
{
	int			status;
	char		*line;
	t_cmds		*cmds;
	t_cmd_list	*list;
	int			i;

	g_ret = 0;
	status = 1;
	initialization(&cmds, envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handle);
	while (status)
	{
		signal(SIGQUIT, sig_handle);
		signal(SIGINT, sig_handle);
		if (cmds->ret != 130)
			ft_putstr_fd("\e[1;31mminishell~>\e[0m ", 1);
		cmds->sig = 0;
		status = get_next_line(0, &line);
		cmds->line = line;
		if (status == 0)
			cmd_exit(list, cmds);
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
				// print_cmds(cmds->cmd_list);
				free_cmd_list(cmds);
			}
			g_ret = 0;
		}
		free(line);
	}
	return (0);
}
