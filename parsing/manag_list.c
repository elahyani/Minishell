/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:53:48 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/17 19:08:39 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_list	*list_cmds(char *data)
{
	t_cmd_list	*head;

	head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	head->line = data;
	head->next = NULL;
	head->prev = NULL;
	head->start = 0;
	head->end = 0;
	head->redir = 0;
	return (head);
}

t_cmd_list	*list_line_cmds(char *data)
{
	t_cmd_list	*head;

	head = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	head->data = data;
	head->p = 0;
	head->next = NULL;
	head->prev =  NULL;
	head->start =  0;
	head->end = 0;
	head->redir = 0;
	if (!head->start)
		head->line = NULL;
	return (head);
}

void	add_front(t_cmd_list **head, t_cmd_list *new)
{
	// new->prev = *head;
	// new->next = (*head)->next ? (*head)->next : NULL;
	// (*head)->next = new;
	// *head = new;
	// new->line = (*head)->line;
	new->next = (*head)->next ? (*head)->next : NULL;
	if ((*head)->next)
		(*head)->next->prev = new;	
	(*head)->next = new;
	new->prev = *head;
	*head = new;
}

// void	update_list(t_cmd_list **head, t_cmd_list **next ,t_cmd_list *new)
// {
// 	new->line = (*next)->line;
// 	new->prev = (*next)->prev;
// 	(*next)->prev = new;
// 	new->next = *next;
// 	if (new->prev != NULL)
// 		new->prev->next = new;
// 	else
// 		*head = new;
// }
