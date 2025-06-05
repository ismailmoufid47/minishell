#include "../include/shell.h"

// void	print_list(t_list *list, int tab_count)
// {
// 	int	i;

// 	i = 0;
// 	if (tab_count == 0)
// 	{
// 		printf("\n");
// 		while (i++ < tab_count)
// 			printf("		");
// 		printf("		LIST\n\n");
// 	}
// 	while (list)
// 	{
// 		i = 0;
// 		while (i++ < tab_count)
// 			printf("		");
// 		if (list->type == HDOC)
// 			printf("      HEREDOC");
// 		else if (list->type == APP)
// 			printf("       APPEND");
// 		else if (list->type == IN)
// 			printf("	 IN");
// 		else if (list->type == OUT)
// 			printf("	 OUT");
// 		else if (list->type == PIPE)
// 		{
// 			printf("       PIPE  FDS:\n");
// 			printf("		IN:%d\n", list->pipe_fds[0]);
// 			printf("		OUT:%d\n", list->pipe_fds[1]);
// 		}
// 		else if (list->type == FIL)
// 			printf("      FILE: %s, quote: %d", list->value, list->quote_type);
// 		else
// 		{
// 			printf("       CMD:  %s, quote: %d", list->value, list->quote_type);
// 			if (list->is_redirected)
// 			{
// 				printf(",  REDIRECTIONS:\n");
// 				print_list(list->redirections, tab_count + 1);
// 			}
// 			printf(" args: \n");
// 			print_tokens(list->args);
// 		}
// 		list = list->next;
// 		if (list)
// 		{
// 			i = 0;
// 			printf("\n");
// 			while (i++ < tab_count)
// 				printf("		");
// 			printf("	  ↓\n");
// 		}
// 	}
// 	printf("\n\n");
// }

t_list	*handle_cmd_red(t_list *head, t_node_type type, int *changed)
{
	t_list	*current;
	t_list	*prev;
	t_list	*prev_prev;

	prev_prev = ((prev = NULL), (current = head), NULL);
	while (current)
	{
		if (current->type == type && prev
			&& prev->type == CMD && current->next && prev_prev)
		{
			prev_prev->next = current;
			prev->next = ((*changed = 1), current->next->next);
			current->next->next = prev;
		}
		else if (current->type == type
			&& prev && prev->type == CMD && current->next && !prev_prev)
		{
			head = current;
			prev->next = current->next->next;
			current->next->next = prev;
			*changed = 1;
		}
		current = ((prev_prev = prev), (prev = current), current->next);
	}
	return (head);
}

// the cmd is always after the redirections
t_list	*remove_red_and_add_it_to_cmd(t_list *head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*cmd;

	current = ((prev = NULL), head);
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
			current = ((cmd->redirections = redirections(current, cmd)), cmd);
		}
		else if (cmd->value == NULL)
			cmd = ((free(cmd)), NULL);
		prev = current;
		if (current == cmd)
			cmd->redirections = keep_only_redirections(cmd->redirections);
		current = current->next;
	}
	return (head);
}

int	count_args(t_list *cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd->type == CMD)
	{
		count++;
		cmd = cmd->next;
	}
	return (count + 1);
}

t_list	*extract_args_and_remove_them(t_list *head)
{
	t_list	*cur;
	t_list	*cmd;
	int		i;

	cur = head;
	while (cur)
	{
		if (cur->type == CMD)
		{
			cur->args = ((i = 0), malloc(sizeof(char *) * (count_args(cur))));
			cmd = cur;
			while (cur && cur->type == CMD)
			{
				cmd->args[i] = cur->value;
				if (cur != cmd)
					cur = ((cmd->next = cur->next), (free(cur)), cmd);
				i++;
				cur = cur->next;
			}
			cmd->args[i] = NULL;
		}
		if (cur)
			cur = cur->next;
	}
	return (head);
}

t_list	*create_list(char **tokens)
{
	char	*tmp;
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
		{
			node = token_to_node(&head, &nav, tokens[i], PIPE);
			pipe_wrapper(node->pipe_fds);
		}
		else if (i && (!ft_strcmp(tokens[i - 1], "<")
				|| !ft_strcmp(tokens[i - 1], ">")
				|| !ft_strcmp(tokens[i - 1], ">>")
				|| !ft_strcmp(tokens[i - 1], "<<")))
			node = token_to_node(&head, &nav, tokens[i], FIL);
		else
		{
			node = token_to_node(&head, &nav, tokens[i], CMD);
			node->is_redirected = 0;
			node->redirections = NULL;
			node->pid = 0;
		}
		if (tokens[i][0] == '\'')
		{
			tmp = node->value;
			node->value = ft_strdup(++node->value);
			free(tmp);
			node->quote_type = SIQUOTED;
		}
		else if (tokens[i][0] == '"')
		{
			tmp = node->value;
			node->value = ft_strdup(++node->value);
			free(tmp);
			node->quote_type = DOQUOTED;
		}
		i++;
	}
	while (1)
	{
		i = 0;
		head = handle_cmd_red(head, IN, &i);
		head = handle_cmd_red(head, OUT, &i);
		head = handle_cmd_red(head, HDOC, &i);
		head = handle_cmd_red(head, APP, &i);
		if (!i)
			break ;
	}
	head = remove_red_and_add_it_to_cmd(head);
	head = extract_args_and_remove_them(head);
	return (head);
}
