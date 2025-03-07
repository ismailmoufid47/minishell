#include "../shell.h"

t_list	*create_list_node(char *token, int type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->value = token;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_list	*redirections(t_list *node, t_list *cmd)
{
	t_list	*head;

	head = node;
	while (node->next && node->next != cmd && node->next != PIPE)
		node = node->next;
	node->next = NULL;
	return (head);
}

t_list	*keep_only_redirections(t_list *head)
{
	t_list	*current;
	t_list	*prev;

	current = head;
	prev = NULL;
	while (current)
	{
		if (current->type != FIL && current->type != IN && current->type != OUT 
			&& current->type != APP && current->type != HDOC)
		{
			if (prev)
				prev->next = NULL;
			return (head);
		}
		prev = current;
		current = current->next;
	}
	return (head);
}

t_list	*closest_cmd(t_list *head)
{
	t_list	*current;
	t_list	*node;

	current = head;
	while (current)
	{
		if (current->type == WRD)
			return (current);
		if (current->type == PIPE)
		{
			node = create_list_node(NULL, WRD);
			node->next = current;
			return (node);
		}
		current = current->next;
	}
	node = create_list_node(NULL, WRD);
	return (node);
}

t_list	*token_to_node(t_list **head, t_list **nav, char *token, int type)
{
	t_list	*node;

	node = create_list_node(token, type);
	if (!*head)
	{
		*head = node;
		*nav = *head;
	}
	else
	{
		(*nav)->next = node;
		*nav = (*nav)->next;
	}
	return (node);
}
