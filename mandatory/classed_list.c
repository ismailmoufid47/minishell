#include "shell.h"

void	print_list(t_list *list)
{
	printf("\n		LIST\n\n");
	while (list)
	{
		if (list->type == IN)
			printf("	 IN:  %s", list->value);
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

	prev_prev = ((prev = NULL), (current = head), NULL);
	while (current)
	{
		if (current->type == type && prev
			&& prev->type == WRD && current->next && prev_prev)
		{
			prev_prev->next = ((tmp = prev), current);
			tmp->next = current->next->next;
			current->next->next = tmp;
		}
		else if (current->type == type
			&& prev && prev->type == WRD && current->next && !prev_prev)
		{
			head = current;
			prev->next = current->next->next;
			current->next->next = prev;
		}
		current = ((prev_prev = prev), (prev = current), current->next);
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
	head = handle_cmd_red(head, IN);
	head = handle_cmd_red(head, OUT);
	return (head);
}

t_list	*token_to_node(t_list **head, t_list **nav, char *token, int type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->value = token;
	node->type = type;
	node->next = NULL;
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

t_list	*find_closest_cmd(t_list *head)
{
	t_list	*current;

	current = head;
	while (current)
	{
		if (current->type == CMD)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// the cmd is always after the redirections
t_list *remove_red_and_add_it_to_cmd(t_list *head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*prev_prev;
	t_list	*tmp;

	while (current)
	{
		if (current->type == IN || current->type == OUT)
		{
			if (current->next && current->next->type == FIL)
			{
				if (prev_prev)
				{
					prev_prev->next = current->next->next;
					find_closest_cmd(current)->redirected_to = tmp;
				}
				else
				{
					head = current->next;
					tmp = current->next;
					current->next = tmp->next;
					tmp->next = current;
				}
			}
		}
		prev = current;
		prev_prev = prev;
		current = current->next;
	}
	return (head);
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
		i++;
	}
	head = join_words(head);
	head = join_words(head);
	return (head);
}

