/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/12 12:52:11 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
{	
	//puts("here");
	while (head)
	{
		head->args = split_cmd(head->data, ' ', cmds);
		// puts("==========================");
		// printf("cmd->args[0] = |%s|\n", head->args[0]);
		// printf("cmd->args[1] = |%s|\n", head->args[1]);
		// puts("==========================");
		if (ft_strcmp(head->args[0], "cd") == 0)
			cmd_cd(head, cmds);
		else if (ft_strcmp(head->args[0], "pwd") == 0)
			cmd_pwd(cmds);
		else if (ft_strcmp(head->args[0], "export") == 0)
			cmd_export(head, cmds);
		else if (ft_strcmp(head->args[0], "unset") == 0)
		{
			//printf("arg[1]==|%s|\n",head->args[1]);
			//printf("arg[2]==|%s|\n",head->args[2]);
			cmd_unset(head, cmds);
		}
		else if (ft_strcmp(head->args[0], "exit") == 0)
			cmd_exit();
		else if (ft_strcmp(head->args[0], "echo") == 0)
			cmd_echo(head);
		else if (ft_strcmp(head->args[0], "env") == 0)
			cmd_env(cmds);
		else if (head->args[0])
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(ft_strtrim(head->args[0], "	"), 1);
			ft_putendl_fd(": command not found", 1);
		}
		// else   
		// 	execve(head->args[0], head->args, cmds->envir);
		if (head->end)
			break ;
		head = head->next;
	}
	return head;
}

void	free_cmd_list(t_cmds *cmds)
{
	t_cmd_list *tmp;

	if (cmds->cmd_list)
	{
		while (cmds->cmd_list)
		{
			tmp = cmds->cmd_list->next;
			free(cmds->cmd_list);
			cmds->cmd_list = tmp;
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
    t_cmds		*cmds;
    t_cmd_list	*list;
    char		*line;
    int			status;
	int			i;

    cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd_list = NULL;
	cmds->index = 0;
	cmds->oldpwd = NULL;
	cmds->cd = 0;
	cmds->minus = 0;
    cmds->envir = envp;
	cmds->index = 0;
	cmds->oldpwd = NULL;
	cmds->save_oldpwd = NULL;
	cmds->cd = 0;
	cmds->minus = 0;
    cmds->env_val = NULL;
    cmds->env_arg = NULL;
	cmds->quote = 0;
	cmds->ignore = 0;
	ft_putstr_fd("\e[1;31mminishell~>\e[0m", 1);
    while ((status = get_next_line(0, &line)) > 0)
    {
        if (ft_strcmp(line, ""))
        {
        	parse_line(&line, cmds);
        	if (cmds->cmd_list)
			{
				list = cmds->cmd_list;
				while (list)
				{
					//printf("***** LINE %s\n", list->line);
					if (!list->line)
						break ;
					parse_list_line(&list->line, list, cmds);
					list = get_cmd(cmds, list);
					if (list)
						list = list->next;
				}
            	print_cmds(cmds->cmd_list);
				free_cmd_list(cmds);
			}
            free(line);
        }
		ft_putstr_fd("\e[1;31mminishell~>\e[0m", 1);
    }
	//free_cmds(cmds);
    return (0);
}

//	free leaks
//	manag sy err
//	$?