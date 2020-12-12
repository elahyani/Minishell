/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elahyani <elahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:53:48 by elahyani          #+#    #+#             */
/*   Updated: 2020/12/08 11:11:39 by elahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	head->next = list ? head->next : NULL;
	head->prev = list ? head->prev : NULL;
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
	new->line = (*next)->line;
	new->prev = (*next)->prev;
	(*next)->prev = new;
	new->next = *next;
	if (new->prev != NULL)
		new->prev->next = new;
	else
		*head = new;
}
