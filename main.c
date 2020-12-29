/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/29 10:31:14 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	sig_handle(int sig)
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

static void	main_init(t_cmds **cmds, char **envp, t_cmd_list **lst, char **tmp)
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
	*tmp = NULL;
	*lst = NULL;
}

static void	run_shell(char *line, t_cmds *cmds, t_cmd_list *list)
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

static void	check_sig(t_cmds **cmds, char **tmp, char **line, int *st)
{
	char	*tmp1;

	if (*tmp)
	{
		tmp1 = ft_strjoin(*tmp, *line);
		*tmp = ft_free_str(*tmp);
		ft_free_str(*line);
		*line = tmp1;
	}
	(*cmds)->line = *line;
	if (*st == 0)
	{
		if (!ft_strlen(*line))
			cmd_exit((*cmds)->cmd_list, *cmds);
		else
		{
			ft_putstr_fd("  \b\b", 1);
			*tmp = ft_strdup(*line);
		}
	}
}

int			main(int argc, char **argv, char **envp)
{
	int			status;
	char		*line;
	char		*tmp;
	t_cmds		*cmds;
	t_cmd_list	*list;

	g_ret = 0;
	status = 1;
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	main_init(&cmds, envp, &list, &tmp);
	signal(SIGQUIT, sig_handle);
	signal(SIGINT, sig_handle);
	while (1)
	{
		if (cmds->ret != 130 && !tmp)
			ft_putstr_fd("\e[1;31mminishell~>\e[0m ", 2);
		cmds->ret = 0;
		status = get_next_line(0, &line);
		check_sig(&cmds, &tmp, &line, &status);
		if (status)
			run_shell(cmds->line, cmds, list);
		g_ret = 0;
		free(line);
	}
	return (0);
}
