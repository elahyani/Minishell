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

t_cmd_list	*get_cmd(t_cmds *cmds, t_cmd_list *head)
{
	while (head)
	{
		head->args = ft_split(head->data, ' ');
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
		if (head->end)
		{
			printf("end ==> |%d|\n", head->end);
			break ;
		}
		head = head->next;
	}
	return head;
}

t_cmd_list	*list_cmds(t_cmd_list *list, char *data, int k)
{
	t_cmd_list	*head;

	if (!list)
		head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	else
		head = list;
	if (k)
		head->data = data;
	else
		head->line = data;
	head->next = NULL;
	head->prev = NULL;
	head->start = 0;
	head->end = 0;
	head->redir = 0;
	return (head);
}

t_cmd_list	*list_line_cmds(t_cmd_list *list, char *data, int k)
{
	t_cmd_list	*head;

	if (!list)
		head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	else
		head = list;
	if (k)
		head->data = data;
	else
		head->line = data;
	head->next = head->next ? head->next : NULL;
	head->prev = head->prev ? head->prev : NULL;
	head->start = list ? head->start : 0;
	head->end = list ? head->end : 0;
	head->redir = list ? head->redir : 0;
	return (head);
}

void	add_front(t_cmd_list **head, t_cmd_list *new)
{
	new->prev = *head;
	new->next = (*head)->next ? (*head)->next : NULL;
	(*head)->next = new;
	*head = new;
}

void	update_list(t_cmd_list **head, t_cmd_list **next ,t_cmd_list *new)
{
	new->prev = (*next)->prev;
	(*next)->prev = new;
	new->next = *next;
	if (new->prev != NULL)
		new->prev->next = new;
	else
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


//**************************************************************************************
//**************************************************************************************
// void	parse_line(char	**line, t_cmds *cmds)										// *
// {																				// *
// 	int		len;																	// *
// 	int		i;																		// *
// 	int		j;																		// *
// 	int		k;																		// *
// 	int		parse_len;							                                    // *
//							                                                        // *
// 	k = -1;																		  	// *
// 	j = 0;																			// *
// 	i = -1;																			// *
// 	parse_len = 0;							                                        // *
// 	cmds->cmd_line = *line;							                                // *
// 	len = ft_strlen(*line);							                                // *
// 	while ((*line)[++i])							                                // *
// 		if ((*line)[i] == ';')						                                // *
// 			parse_len++;							                                // *
// 	cmds->f_parse_line = (char **)malloc(sizeof(char *) * (parse_len));				// *
// 	i = -1;																			// *
// 	while (++i <= len)																// *
// 	{																				// *
// 		if (((*line)[i] == ';' || (*line)[i] == '\0') && k != -1)					// *
// 		{																			// *
// 			cmds->f_parse_line[++j] = ft_substr(*line, k, i - k);					// *
// 			printf("line [%d] = |%s|\n",j, cmds->f_parse_line[j]);					// *
// 			k = -1;																	// *
// 		}																			// *
// 		else if (k == -1)															// *
// 			k = i;																	// *
// 	}																				// *
// }																				// *
//**************************************************************************************
//**************************************************************************************

void	parse_line(char	**line, t_cmds *cmds)
{	
	t_cmd_list *head;
	t_cmd_list *new_node;
	int		len;
	int		i;

	i = -1;
	cmds->cmd_line = *line;
	len = ft_strlen(*line);
	head = list_cmds(NULL, cmds->cmd_line, 0);
	while (++i <= len)
	{
		if ((*line)[i] == ';' || (*line)[i] == '\0')
		{
			if ((*line)[i] == ';')
			{
				(*line)[i] = '\0';
				add_front(&head, list_cmds(NULL, *line + i + 1, 0));
			}
		}
	}
	while (head->prev != NULL)
		head = head->prev;
	cmds->cmd_list = head;
}

void	parse_list_line(char **line_list, t_cmd_list *list, t_cmds *cmds)
{	
	int			len;
	int			i;
	int			l;
	char		*tmp;
	char		*tmp1;
	char		tmp2[2];
	char		*arg;
	t_cmd_list	*head;

	tmp = NULL;
	tmp1 = NULL;
	i = -1;
	len = ft_strlen(*line_list);
	arg = ft_strdup("");
	while (++i <= len)
	{ 
		if ((*line_list)[i] == '$')
		{
			l = b_point(*line_list + i);
			cmds->join_arg = ft_substr(*line_list + i, 0, l);
			cmds->env_val = get_env_val(cmds, cmds->join_arg);
			tmp = ft_strjoin(arg, cmds->env_val);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp);
			i += l - 1;
		}
		else
		{
			tmp2[0] = (*line_list)[i];
			tmp2[1] = '\0';
			tmp1 = ft_strjoin(arg, tmp2);
			(arg) ? free(arg) : 0;
			arg = ft_strdup(tmp1);
		}
	}
	*line_list = ft_strdup(arg);
	(arg) ? free(arg) : 0;
	(tmp) ? free(tmp) : 0;
	(tmp1) ? free(tmp1) : 0;
	len = ft_strlen(*line_list);
	head = list_line_cmds(list, *line_list, 1);
	i = -1;
	while (++i <= len)
	{
		if ((*line_list)[i] == ';' || (*line_list)[i] == '\0')
		{
			if (!head->prev || (head->prev && head->prev->end))
				head->start = 1;
			head->end = 1;
			if ((*line_list)[i] == ';' )
				break ;
		}
		else if ((*line_list)[i] == '|')
		{
			if (!head->prev || (head->prev && head->prev->end))
				head->start = 1;
			(*line_list)[i] = '\0';
			add_front(&head, list_line_cmds(NULL, *line_list + i + 1, 1));
		}
		else if ((*line_list)[i] == '<')
			head->redir = '<';
		else if ((*line_list)[i] == '>')
		{
			if ((*line_list)[i + 1] == '>')
			{
				head->redir = 'a';
				i++;
			}
			else
				head->redir = '>';
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
    t_cmds	*cmds;
    t_cmd_list *list;
    char	*line;
    int		status;

    cmds = (t_cmds *)malloc(sizeof(t_cmds));
    cmds->cmd_list = malloc(sizeof(t_cmd_list));
    list = malloc(sizeof(t_cmd_list));
    cmds->envir = envp;
    cmds->env_val = NULL;
    cmds->env_arg = NULL;
    list->line = NULL;
    ft_putstr_fd("minishell>", 1);
    while ((status = get_next_line(0, &line)) > 0)
    {
        if (ft_strcmp(line, ""))
        {
            parse_line(&line, cmds);
           list = cmds->cmd_list;
           while (list)
           {
               printf("***** LINE %s\n", list->line);
               if (!list->line)
                   break ;
               parse_list_line(&list->line, list, cmds);
               list = get_cmd(cmds, list);
               list = list->next;
           }
            print_cmds(cmds->cmd_list);
            free(line);
        }
        ft_putstr_fd("minishell>", 1);
    }
    return (0);
}

// echo $PWD; echo $OLDPWD; cd .; pwd; echo $PWD; echo $OLDPWD
// cd '' ; echo $PWD