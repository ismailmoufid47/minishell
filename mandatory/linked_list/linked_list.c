#include "../shell.h"

void	print_list(t_list *list, int tab_count)
{
	int	i;

	i = 0;
	printf("\n");
	while (i++ < tab_count)
		printf("		");
	printf("		LIST\n\n");
	while (list)
	{
		i = 0;
		while (i++ < tab_count)
			printf("		");
		if (list->type == HDOC)
			printf("      HEREDOC");
		else if (list->type == APP)
			printf("       APPEND");
		else if (list->type == IN)
			printf("	 IN");
		else if (list->type == OUT)
			printf("	 OUT");
		else if (list->type == PIPE)
			printf("	PIPE");
		else if (list->type == FIL)
			printf("      FILE: %s", list->value);
		else
		{
			printf("       CMD:  %s", list->value);
			if (list->is_redirected)
			{
				printf(",  REDIRECTIONS:\n");
				print_list(list->redirections, tab_count + 1);
			}
		}
		list = list->next;
		if (list)
		{
			i = 0;
			printf("\n");
			while (i++ < tab_count)
				printf("		");
			printf("	  ↓\n");
		}
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
	head = handle_cmd_red(head, HDOC);
	head = handle_cmd_red(head, APP);
	return (head);
}


// the cmd is always after the redirections
t_list *remove_red_and_add_it_to_cmd(t_list *head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*cmd;

	current = head;
	prev = NULL;
	while (current)
	{
		cmd = closest_cmd(current);
		if (current->type == IN || current->type == OUT
			|| current->type == APP || current->type == HDOC)
		{
			if (prev)
				prev->next = cmd;
			if (head == current)
				head = cmd;
			cmd->is_redirected = 1;
			cmd->redirections = redirections(current, cmd);
			cmd->redirections = keep_only_redirections(cmd->redirections);
			current = cmd;
		}
		prev = current;
		current = current->next;
	}
	return (head);
}

t_list	*create_list(char **tokens)
{
	t_list	*nav;
	t_list	*head;
	t_list	*node;
	int		i;

	i = 0;
	nav = ((head = NULL), NULL);
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<<"))
			token_to_node(&head, &nav, tokens[i], HDOC);
		else if (!ft_strcmp(tokens[i], ">>"))
			token_to_node(&head, &nav, tokens[i], APP);
		else if (!ft_strcmp(tokens[i], "<"))
			token_to_node(&head, &nav, tokens[i], IN);
		else if (!ft_strcmp(tokens[i], ">"))
			token_to_node(&head, &nav, tokens[i], OUT);
		else if (!ft_strcmp(tokens[i], "|"))
			token_to_node(&head, &nav, tokens[i], PIPE);
		else if (i && (!ft_strcmp(tokens[i - 1], "<")
				|| !ft_strcmp(tokens[i - 1], ">")
				|| !ft_strcmp(tokens[i - 1], ">>")
				|| !ft_strcmp(tokens[i - 1], "<<")))
			token_to_node(&head, &nav, tokens[i], FIL);
		else
		{
			node = token_to_node(&head, &nav, tokens[i], WRD);
			node->is_redirected = 0;
			node->redirections = NULL;
		}
		i++;
	}
	head = join_words(head);
	head = join_words(head);
	head = remove_red_and_add_it_to_cmd(head);
	return (head);
}
