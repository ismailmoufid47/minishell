/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   expand_bonus.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

t_list	*create_list_node(char *token, int type)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->value = token;
	node->type = type;
	node->quote_type = UNQUOTED;
	node->redirected = 0;
	node->redirs = NULL;
	node->args = NULL;
	node->pid = 0;
	node->next = NULL;
	node->here_doc = 0;
	return (node);
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

t_list	*closest_cmd(t_list *head)
{
	t_list	*current;
	t_list	*node;

	current = head;
	while (current)
	{
		if (current->type == CMD)
			return (current);
		if (current->type == PIPE)
		{
			node = create_list_node(NULL, CMD);
			node->next = current;
			return (node);
		}
		current = current->next;
	}
	node = create_list_node(NULL, CMD);
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
