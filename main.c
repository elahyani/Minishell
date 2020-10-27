/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/10/27 19:39:32 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd(t_cmds *cmds)
{
	//printf("|%s|\n", cmds->cmd[0]);
	if (ft_strcmp(cmds->cmd[0], "cd") == 0)
		cmd_cd(cmds);
	if (ft_strcmp(cmds->cmd[0], "echo") == 0)
		cmd_echo(cmds);
	else if (ft_strcmp(cmds->cmd[0], "pwd") == 0)
		cmd_pwd();
	// else if (ft_strcmp(cmds->cmd[0], "export") == 0)
	// 	cmd_export();
	// else if (ft_strcmp(cmds->cmd[0], "unset") == 0)
	// 	cmd_unset();
	// else if (ft_strcmp(cmds->cmd[0], "env") == 0)
	// 	cmd_env();
	else if (ft_strcmp(cmds->cmd[0], "exit") == 0)
		cmd_exit();
	//else   
		//execve();
}

void	parse_line(char	**line, t_cmds *cmds)
{	
	int		len;
	int		len1;
	int		i;
	
	i = 0;
	cmds->counter = 0;
	len = ft_strlen(*line);	
	while (i++ <= len)
		((*line)[i] == ' ') ? cmds->counter++ : 0;
	cmds->cmd = ft_split(*line, ' ');
	get_cmd(cmds);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmds	cmds;

	cmds.envir = envp;
	dprintf(0, "minishell>");
	while ((get_next_line(0, &line)) > 0)
	{
		parse_line(&line, &cmds);
		dprintf(0, "minishell>");
		free(line);
	}
	return (0);
}