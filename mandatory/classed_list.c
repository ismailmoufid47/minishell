#include "shell.h"

void	print_list(t_list *list)
{
	printf("\t\tLIST\n");
	while (list)
	{
		if (list->type == IN)
			printf("	IN:   %s", list->value);
		else if (list->type == OUT)
			printf("	 OUT: %s", list->value);
		else if (list->type == PIPE)
			printf("	PIPE: %s", list->value);
		else if (list->type == FIL)
			printf("	FILE: %s", list->value);
		else
			printf("	WORD: %s", list->value);
		list = list->next;
		if (list)
			printf("\n	  ↓\n");
	}
	printf("\n");
}

t_list	*handle_cmd_red(t_list *head, t_node_type type)
{
	t_list	*current;
	t_list	*tmp;
	t_list	*prev;
	t_list	*prev_prev;

	current = head;
	prev = NULL;
	prev_prev = NULL;
	while (current)
	{
		if (current->type == type && prev && prev->type == WRD && current->next && prev_prev)
		{
			tmp = prev;
			prev_prev->next = current;
			tmp->next = current->next->next;
			current->next->next = tmp;
		}
		else if (current->type == type && prev && prev->type == WRD && current->next && !prev_prev)
		{
			head = current;
			prev->next = current->next->next;
			current->next->next = prev;
		}
		prev_prev = prev;
		prev = current;
		current = current->next;
	}
	return (head);
}

t_list	*join_words(t_list *head)
{
	t_list	*current;
	t_list	*tmp;

	current = head;
	while (current)
	{
		if (current->type == WRD && current->next && current->next->type == WRD)
		{
			current->value = ft_strjoin(current->value, " ");
			current->value = ft_strjoin(current->value, current->next->value);
			tmp = current->next;
			current->next = tmp->next;
			free(tmp);
			current = head;
			continue ;
		}
		current = current->next;
	}
	// head = handle_cmd_red(head,IN);
	head = handle_cmd_red(head,OUT);
	//head = handle_cmd_aftr_out(head);
	return (head);
}

t_list	*create_node(char *value, t_node_type type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->value = value;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	token_to_node(t_list **head, t_list **nav, char *token, int type)
{
	if (!*head)
	{
		*head = create_node(token, type);
		*nav = *head;
	}
	else
	{
		(*nav)->next = create_node(token, type);
		*nav = (*nav)->next;
	}
}

t_list	*create_list(char **tokens)
{
	t_list	*nav;
	t_list	*head;
	int		i;

	i = 0;
	nav = ((head = NULL), NULL);
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<"))
			token_to_node(&head, &nav, tokens[i], IN);
		else if (!ft_strcmp(tokens[i], ">"))
			token_to_node(&head, &nav, tokens[i], OUT);
		else if (!ft_strcmp(tokens[i], "|"))
			token_to_node(&head, &nav, tokens[i], PIPE);
		else if (i && (!ft_strcmp(tokens[i - 1], "<")
				|| !ft_strcmp(tokens[i - 1], ">")))
			token_to_node(&head, &nav, tokens[i], FIL);
		else
			token_to_node(&head, &nav, tokens[i], WRD);
		printf("token : %s node : %s\n", tokens[i], nav->value);
		i++;
	}
	head = join_words(head);
	printf("\naffa\n");
	head = join_words(head);
	return (head);
}

