/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/05 13:20:48 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_to_file(char *s, char *num, int end)
{
	FILE *f;
	int fd;

	f = fopen("debug.txt", "a");
	fd = fileno(f);
	ft_putstr_fd(s, fd);
	if (num)
		ft_putstr_fd(num, fd);
	if (end)
		ft_putstr_fd("\n-------\n", fd);
	fclose(f);
}

void	erase_file_debug()
{
	FILE *f;
	int fd;

	f = fopen("debug.txt", "w");
	fd = fileno(f);
	ft_putstr_fd("", fd);
	fclose(f);
}

void	get_cmd(t_cmds *cmds)
{
	if (ft_strcmp(cmds->cmd_line, "cd") == 0)
		cmd_cd(cmds);
	else if (ft_strcmp(cmds->cmd_line, "echo") == 0)
		cmd_echo(cmds);
	else if (ft_strcmp(cmds->cmd_line, "pwd") == 0)
		cmd_pwd(cmds);
	// else if (ft_strcmp(cmds->cmd_line, "export") == 0)
	// 	cmd_export();
	// else if (ft_strcmp(cmds->cmd_line, "unset") == 0)
	// 	cmd_unset();
	else if (ft_strcmp(cmds->cmd_line, "env") == 0)
		cmd_env(cmds);
	else if (ft_strcmp(cmds->cmd_line, "exit") == 0)
		cmd_exit();
	// else   
	// 	execve(cmds->cmd_line, cmds->cmd, cmds->envir);
}

t_cmd_list	*list_cmds(char *data)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)malloc(sizeof(t_list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void	add_front(t_cmd_list **head, t_cmd_list *new)
{
	//hnaaaa fin anzido cmds;
	new->next = *head;
	new->prev = NULL;
	// if (*head)
	// 	(*head)->prev = NULL;
	*head = new;
}

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	t_cmd_list *new_node;
	int		len;
	int		i;
	
	i = 0;
	cmds->counter = 0;
	cmds->sep = 0;
	if (!ft_strcmp(*line, ""))
		return ;
	len = ft_strlen(*line);
	cmds->cmd = ft_split(*line, ';');
	while (i++ <= len)
	{
		if (cmds->sep == 0)
				head = list_cmds(cmds->cmd[0]);
		if ((*line)[i] == ' ')
			cmds->counter++;
		else if ((*line)[i] == ';' || (*line)[i] == '|')
		{
			(*line)[i] = '\0';
			// printf(" first cmd = |%s|\n", *line);
			add_front(&head, list_cmds(*(line) + i + 1));
			// printf("second cmd = |%s|\n", *line + i + 1);
			cmds->sep++;
		}
	}
	// puts(cmds->cmd[0]);
	// puts(cmds->cmd[1]);
	// i = -1;
	// while (++i <= cmds->sep)
	// {
		
	// 	// add_front(&head, list_cmds(cmds->cmd[i]));
	// 	// printf("cmd -> |%s|\n", head->next->data);
	// 	// printf("cmd line [%d] -> |%s|\n", i, head->data);
	// }
	while (head != NULL)
	{
		ft_putendl_fd(head->data, 1);
		head = head->next;
	}
	// ft_putendl_fd(head->next->data, 1);
	cmds->cmd_line = cmds->cmd[0];
	cmds->arg = cmds->cmd[1];
	get_cmd(cmds);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmds	cmds;
	int		status;

	erase_file_debug();
	cmds.envir = envp;
	cmds.start = 0;
	ft_putstr_fd("minishell>", 1);
	while ((status = get_next_line(0, &line)) > 0)
	{
		parse_line(&line, &cmds);
		ft_putstr_fd("minishell>", 1);
		free(line);
	}
	return (0);
}