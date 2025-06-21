/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   classed_list_bonus.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

void print_args(t_list *list)
{
	int i;
	i = 0;
	printf("\nARGS:\n");
	while(list->args[i])
	{
		printf("%d: %s\n", i, list->args[i]);
		i++;
	}
	printf("\n\n");
}
void	print_list2(t_list *list, int tab_count)
{
	int	i;

	i = 0;
	if (tab_count == 0)
	{
		printf("\n");
		while (i++ < tab_count)
			printf("		");
		printf("		LIST\n\n");
	}
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
		{
			printf("       PIPE  FDS:\n");
			printf("		IN:%d\n", list->pipe_fds[0]);
			printf("		OUT:%d\n", list->pipe_fds[1]);
		}
		else if (list->type == FIL)
			printf("      FILE: %s, quote: %d", list->value, list->quote_type);
		else
		{
			printf("       CMD:  %s, quote: %d", list->value, list->quote_type);
			if (list->redirected)
			{
				printf(",  REDIRECTIONS:\n");
				print_list2(list->redirs, tab_count + 1);
			}
			printf(" args: \n");
			if (list->args)
				print_args(list);
			else
				printf("		No args\n");
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
	printf("\n\n");
}


t_list	*extract_args_and_remove_them(t_list *head)
{
	t_list	*cur;
	t_list	*head_cmd;

	cur = head;
	while (cur)
	{
		if (cur->type == CMD)
		{
			cur->args = match_wild_card(cur);
			head_cmd = cur;
			while (cur && cur->type == CMD)
			{
				head_cmd->next = cur->next;
				cur = cur->next;
			}
		}
		if (cur)
			cur = cur->next;
	}
	return (head);
}

t_list	*reform_list(t_list *head, int *i)
{
	while (1)
	{
		*i = 0;
		head = handle_cmd_red(head, IN, i);
		head = handle_cmd_red(head, OUT, i);
		head = handle_cmd_red(head, HDOC, i);
		head = handle_cmd_red(head, APP, i);
		if (!*i)
			break ;
	}
	head = remove_red_and_add_it_to_cmd(head);
	head = extract_args_and_remove_them(head);
	return (head);
}

t_list	*create_list(t_list *head, t_list *nav, char **tokens)
{
	char	*tmp;
	char	*prev_token;
	t_list	*node;
	int		i;

	nav = ((i = -1), (prev_token = NULL), (head = NULL), NULL);
	while (tokens[++i])
	{
		if (handle_special_node(tokens[i], &head, &nav))
			;
		else if (i && is_special_token(prev_token) && *prev_token != '|')
			node = token_to_node(&head, &nav, tokens[i], FIL);
		else
			node = token_to_node(&head, &nav, tokens[i], CMD);
		prev_token = (free(prev_token), (ft_strdup(tokens[i])));
		if (tokens[i][0] == '\'')
			node->quote_type = ((tmp = tokens[i]), (tokens[i]
						= ft_strdup(tokens[i] + 1)), node->value = tokens[i],
					(free(tmp)), SIQUOTED);
		else if (tokens[i][0] == '"')
			node->quote_type = ((tmp = tokens[i]), (tokens[i]
						= ft_strdup(tokens[i] + 1)), node->value = tokens[i],
					(free(tmp)), DOQUOTED);
	}
	return (free(prev_token), reform_list(head, &i));
}
