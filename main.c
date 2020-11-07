	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:09:30 by elahyani          #+#    #+#             */
/*   Updated: 2020/11/07 12:17:38 by elahyani         ###   ########.fr       */
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

void	get_cmd(t_cmds *cmds, char	*arg)
{
	//puts(arg);
	cmds->args = ft_split(arg, ' ');
	puts("==========================");
	printf("cmd->args[0] = |%s|\n", cmds->args[0]);
	printf("cmd->args[1] = |%s|\n", cmds->args[1]);
	puts("==========================");
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		cmd_cd(cmds);
	else if (ft_strcmp(cmds->args[0], "echo") == 0)
		cmd_echo(cmds);
	else if (ft_strcmp(cmds->args[0], "pwd") == 0)
		cmd_pwd(cmds);
	// else if (ft_strcmp(cmds->args[0], "export") == 0)
	// 	cmd_export();
	// else if (ft_strcmp(cmds->args[0], "unset") == 0)
	// 	cmd_unset();
	else if (ft_strcmp(cmds->args[0], "env") == 0)
		cmd_env(cmds);
	else if (ft_strcmp(cmds->args[0], "exit") == 0)
		cmd_exit();
	// else   
	// 	execve(cmds->args[0], cmds->args, cmds->envir);
}

t_cmd_list	*list_cmds(char *data)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

int		ft_getsep(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			// s[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}


void	add_front(t_cmd_list **head, t_cmd_list *new)
{
	new->prev = *head;
	new->next = NULL;
	(*head)->next = new;
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
	cmds->cmd_line = *line;
	if (!ft_strcmp(*line, ""))
		return ;
	len = ft_strlen(*line);
	if (ft_getsep(cmds->cmd_line, ';') == 1)
		cmds->cmd = ft_split(*line, ';');
	else if (ft_getsep(cmds->cmd_line, '|') == 1)
		cmds->cmd = ft_split(*line, '|');
	while (i++ <= len)
	{
		if (cmds->sep == 0)
			head = list_cmds(cmds->cmd_line);
		if ((*line)[i] == ' ')
			cmds->counter++;
		else if ((*line)[i] == ';' || (*line)[i] == '|')
		{
			(*line)[i] = '\0';
			add_front(&head, list_cmds(*(line) + i + 1));
			cmds->sep++;
		}
	}
	while (head->prev != NULL)
		head = head->prev;
	while (head != NULL)
	{
		get_cmd(cmds, head->data);
		head = head->next;
	}
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