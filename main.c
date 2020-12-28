/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/28 12:44:24 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		if (g_ret < 2)
		{
			ft_putstr_fd("\b\b  \b\b\n", 2);
			ft_putstr_fd("\e[1;31mminishell\e[0m\033[0;33m~>\033[0m ", 2);
		}
		g_ret = g_ret >= 2 ? 2 : 1;
	}
	else if (sig == SIGQUIT)
	{
		if (g_ret != 2)
			ft_putstr_fd("\b\b  \b\b", 2);
	}
}

void	initialization(t_cmds **cmds, char **envp)
{
	int		i;

	i = -1;
	(*cmds)->ret = 0;
	(*cmds)->quote = 0;
	(*cmds)->pwd = NULL;
	(*cmds)->ignore = 0;
	(*cmds)->envir = (char **)malloc(sizeof(char*) * (ft_arr_len(envp) + 1));
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			(*cmds)->envir[i] = ft_strdup("OLDPWD");
		else
			(*cmds)->envir[i] = ft_strdup(envp[i]);
	}
	(*cmds)->envir[i] = NULL;
	(*cmds)->oldpwd = NULL;
	(*cmds)->env_val = NULL;
	(*cmds)->env_arg = NULL;
	(*cmds)->cmd_list = NULL;
	(*cmds)->save_oldpwd = NULL;
}

void	run_shell(char *line, t_cmds *cmds, t_cmd_list *list)
{
	if (ft_strcmp(line, ""))
	{
		parse_line(&line, cmds);
		if (cmds->cmd_list)
		{
			g_ret = !g_ret ? 2 : 3;
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

	g_ret = 0;
	status = 1;
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	initialization(&cmds, envp);
	signal(SIGQUIT, sig_handle);
	signal(SIGINT, sig_handle);
	while (status)
	{
		(cmds->ret != 130) ? ft_putstr_fd("\e[1;31mminishell~>\e[0m ", 2) : 0;
		cmds->ret = 0;
		status = get_next_line(0, &line);
		cmds->line = line;
		(status == 0) ? cmd_exit(list, cmds) : 0;
		run_shell(line, cmds, list);
		g_ret = 0;
		free(line);
	}
	return (0);
}
