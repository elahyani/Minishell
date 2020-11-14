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

void	get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	while (head)
	{
		head->args = ft_split(head->data, ' ');
		puts("==========================");
		printf("cmd->args[0] = |%s|\n", head->args[0]);
		printf("cmd->args[1] = |%s|\n", head->args[1]);
		puts("==========================");
		if (ft_strcmp(head->args[0], "cd") == 0)
			cmd_cd(head);
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

void	add_front(t_cmd_list **head, t_cmd_list *new)
{
	new->prev = *head;
	new->next = NULL;
	(*head)->next = new;
	*head = new;
}

char	*get_env_val(t_cmds *cmds, char *join_arg)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (cmds->env_val)
		free(cmds->env_val);
	cmds->env_val = ft_strdup(join_arg + 1);
	while (cmds->envir[j] != NULL)
	{
		cmds->env_line = ft_split(cmds->envir[j], '=');
		if (ft_strcmp(cmds->env_line[0], cmds->env_val) == 0)
		{
			k = 1;
			return (cmds->env_line[1]);
		}
		j++;
	}
	if (k == 0)
		return (cmds->join_arg);
	return (NULL);
}

int		b_point(char *arg)
{
	int i;

	i = 0;
	while (arg[++i])
		if (ft_strchr("$\\\"';| ", arg[i]))
			return (i);
	return (i);
}

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	t_cmd_list *new_node;
	int		len;
	int		i;
	int		l;
	char	*tmp;
	char	*tmp1;
	char	tmp2[2];
	char	*arg;

	tmp = NULL;
	tmp1 = NULL;
	i = -1;
	head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	len = ft_strlen(*line);
	arg = ft_strdup("");
	while (++i <= len)
	{
		if ((*line)[i] == '$')
		{
			l = b_point(*line + i);
			cmds->join_arg = ft_substr(*line + i, 0, l);
			cmds->env_val = get_env_val(cmds, cmds->join_arg);
			tmp = ft_strjoin(arg, cmds->env_val);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp);
			i += l - 1;
		}
		else
		{
			tmp2[0] = (*line)[i];
			tmp2[1] = '\0';
			tmp1 = ft_strjoin(arg, tmp2);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp1);
		}
	}
	*line = ft_strdup(arg);
	(arg) ? free(arg) : 0;
	(tmp) ? free(tmp) : 0;
	(tmp1) ? free(tmp1) : 0;
	i = -1;
	cmds->cmd_line = *line;
	len = ft_strlen(*line);
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