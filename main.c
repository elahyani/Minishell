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

char	*get_env_val(t_cmds *cmds, char *line)
{
	int		j;

	j = 0;
	if (cmds->env_val)
		free(cmds->env_val);
	cmds->env_val = ft_strdup(line + 1);
	while (cmds->envir[j] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[j], '=');
		if (ft_strcmp(cmds->env_line[0], cmds->env_val) == 0)
			return (cmds->env_line[1]);
		j++;
	}
	return (NULL);
}

int		b_point(char *arg)
{
	int i;

	i = 0;
	printf("arg ==> |%s|\n", arg);
	while (arg[++i])
		if (ft_strchr("$\\\"'", arg[i]))
			return (i);
	return (i);
}

void	get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	int		i;
	int 	j;
	int 	l;
	char	*arg;
	char	*tmp;
	char	*tmp1;
	char	tmp2[2];

	while (head)
	{
		// if (!ft_strcmp(cmds->cmd_line, ""))
		// 	return ;
		head->args = ft_split(head->data, ' ');
		i = 0;
		while (head->args[i])
		{	
			arg = ft_strdup("");
			j = 0;
			while (head->args[i][j])
			{
				if (head->args[i][j] == '$')
				{
					l = b_point(head->args[i] + j);
					cmds->join_arg = ft_substr(head->args[i] + j, 0, l);
					cmds->env_val = get_env_val(cmds, cmds->join_arg);
					// printf("cmds->env_val = |%s|\n", cmds->env_val);
					puts(cmds->join_arg);
					puts(cmds->env_val);
					puts("------------");
					tmp = ft_strjoin(arg, cmds->env_val);
					free(arg);
					arg = tmp;
					j += l -1;
				}
				else
				{
					tmp2[0] = head->args[i][j];
					tmp2[1] = '\0';
					tmp1 = ft_strjoin(arg, tmp2);
					free(arg);
					arg = tmp1;
				}
				j++;
			}
			head->args[i] = arg;
			i++;
		}
		puts("==========================");
		printf("cmd->args[0] = |%s|\n", head->args[0]);
		printf("cmd->args[1] = |%s|\n", head->args[1]);
		puts("==========================");
		// if (ft_strcmp(head->args[0], "cd") == 0)
		// 	cmd_cd(head);
		// else if (ft_strcmp(head->args[0], "echo") == 0)
		// 	cmd_echo(head);
		// else if (ft_strcmp(head->args[0], "pwd") == 0)
		// 	cmd_pwd(head);
		// // else if (ft_strcmp(head->args[0], "export") == 0)
		// // 	cmd_export();
		// // else if (ft_strcmp(head->args[0], "unset") == 0)
		// // 	cmd_unset();
		// else if (ft_strcmp(head->args[0], "env") == 0)
		// 	cmd_env(head);
		// else if (ft_strcmp(head->args[0], "exit") == 0)
		// 	cmd_exit();
		// else   
		// 	execve(head->args[0], head->args, cmds->envir);
		head = head->next;
	}
}

t_cmd_list	*list_cmds(char *data)
{
	t_cmd_list	*list;

	list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	list->start = 0;
	list->end = 0;
	list->redir = 0;
	return (list);
}

// int		ft_getsep(char *s, int c)
// {
// 	int		i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	add_front(t_cmd_list **head, t_cmd_list *new)
{
	new->prev = *head;
	new->next = NULL;
	(*head)->next = new;
	*head = new;
}

void	get_new_line(char **line, t_cmds *cmds, int *len, t_cmd_list **head)
{
	int i;
	
	i = -1;
	while (++i <= *len)
	{
		if ((*line)[i] == '$')
		{
			puts("here 6");
			cmds->env_arg = get_env_val(cmds, *line + i);
			puts("here 5");
			cmds->env_val = ft_substr(*line, 0, i);
			puts("here 4");
			*line = ft_strjoin(cmds->env_val, cmds->env_arg);
			puts("here 3");
			cmds->cmd_line = *line;
			puts("here 2");
			*head = list_cmds(cmds->cmd_line);
			puts("here 1");
			return ;
		}
	}
}

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	t_cmd_list *new_node;
	int		len;
	int		i;
	
	i = -1;
	head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	len = ft_strlen(*line);

	// if (ft_getsep(cmds->cmd_line, ';') == 1)
	// 	cmds->cmd = ft_split(*line, ';');
	// else if (ft_getsep(cmds->cmd_line, '|') == 1)
	// 	cmds->cmd = ft_split(*line, '|');
	

	i = -1;
	cmds->cmd_line = *line;
	head = list_cmds(cmds->cmd_line);
	while (++i <= len)
	{
		if ((*line)[i] == ';' || (*line)[i] == '\0')
		{
			if (!head->prev || (head->prev && head->prev->end))
				head->start = 1;
			head->end = 1;
			if ((*line)[i] == ';')
			{
				(*line)[i] = '\0';
				add_front(&head, list_cmds(*(line) + i + 1));
			}
		}
		else if ((*line)[i] == '|')
		{
			if (!head->prev || (head->prev && head->prev->end))
				head->start = 1;
			(*line)[i] = '\0';
			add_front(&head, list_cmds(*(line) + i + 1));
		}
		else if ((*line)[i] == '<')
			head->redir = '<';
		else if ((*line)[i] == '>')
		{
			if ((*line)[i + 1] == '>')
			{
				head->redir = 'a';
				i++;
			}
			else
				head->redir = '>';
		}
	}
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmds	*cmds;
	int		status;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmd_list = malloc(sizeof(t_cmd_list));
	cmds->envir = envp;
	cmds->env_val = NULL;
	cmds->env_arg = NULL;
	ft_putstr_fd("minishell>", 1);

	while ((status = get_next_line(0, &line)) > 0)
	{
		if (ft_strcmp(line, ""))
		{
			parse_line(&line, cmds);
			get_cmd(cmds, cmds->cmd_list);
			print_cmds(cmds->cmd_list);
			free(line);
		}
		ft_putstr_fd("minishell>", 1);
	}
	return (0);
}