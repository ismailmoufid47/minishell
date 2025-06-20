/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   classed_list_redirections_bonus.c                   :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

t_list	*redirs(t_list *node, t_list *cmd)
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

// the cmd is always after the redirs
t_list	*remove_red_and_add_it_to_cmd(t_list *head)
{
	t_list	*cr;
	t_list	*prev;
	t_list	*cmd;

	cr = ((prev = NULL), head);
	while (cr)
	{
		cmd = closest_cmd(cr);
		if (cr->type == IN || cr->type == OUT
			|| cr->type == APP || cr->type == HDOC)
		{
			if (prev)
				prev->next = cmd;
			if (head == cr)
				head = cmd;
			cr = ((cmd->redirected = 1), (cmd->redirs = redirs(cr, cmd)), cmd);
		}
		else if (cmd->value == NULL)
			cmd = ((free(cmd)), NULL);
		prev = cr;
		if (cr == cmd)
			cmd->redirs = keep_only_redirections(cmd->redirs);
		cr = cr->next;
	}
	return (head);
}

int	handle_special_node(char *token, t_list **head, t_list **nav)
{
	if (!ft_strcmp(token, "<<"))
		return (token_to_node(head, nav, token, HDOC), 1);
	else if (!ft_strcmp(token, ">>"))
		return (token_to_node(head, nav, token, APP), 1);
	else if (!ft_strcmp(token, "<"))
		return (token_to_node(head, nav, token, IN), 1);
	else if (!ft_strcmp(token, ">"))
		return (token_to_node(head, nav, token, OUT), 1);
	else if (!ft_strcmp(token, "|"))
	{
		pipe_wrapper(token_to_node(head, nav, token, PIPE)->pipe_fds);
		return (1);
	}
	return (0);
}
