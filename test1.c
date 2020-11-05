#include <stdlib.h>

typedef struct s_list
{
	int		data;
	struct s_list *next;
	struct s_list *prev;
}				t_list;

t_list		*new_list(int data)
{
	t_list		*list;

	list = (t_list *)malloc(sizeof(t_list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return list;
}


// void	add_end(t_list **head, t_list *end)
// {
// 	t_list *new = *head;

// 	end->next = NULL;
// 	if (*head == NULL)
// 	{
// 		end->prev = NULL;
// 		*head = end;
// 		return ;
// 	}
// 	while (new->next != NULL)
// 		new = new->next;
// 	new->next = end;
// 	end->prev = new;
// }

void		add_front(t_list **head, t_list *new)
{
		new->next = *head;
		new->prev = NULL;
		// if (*head)
		// 	(*head)->prev = new;
		*head = new;
}

int		main(int argc, char **argv, char **env)
{
	
	t_list *list;

	int i= 0;
	while(++i < 124567)
		add_front(&list, new_list(2147483647));
	// while (list && list->prev)
	// 	list = list->prev;
	// t_list	*end = new_list(7);
	// add_end(&list, end);


	// printf("%p %d %d\n", list->prev, list->data, list->next->next->data);
	// printf("%p %d %d\n", new->prev, new->data, new->next->data);
	// printf("%d %d %p\n", end->prev->data, end->data, end->next);

	// printf("%d %d\n", new->next->data, new->next->prev->data);
	// printf("%d %d\n", end->next->data, end->next->prev->data);
	// printf("%d %d %d\n", list->prev->data, list->data ,list->next->data);
	// printf("%d %d %d\n", new->prev->data, new->data ,new->next->data);
	// printf("%d %d %d\n", end->prev->data, end->data ,end->next->data);
	return (0);
}


// int		main(int argc, char **argv, char **env)
// {
	
// 	t_list *list;
// 	list = new_list(5);

// 	t_list	*new = new_list(6);

// 	add_front(&list, new);
// 	new->next = NULL;

	