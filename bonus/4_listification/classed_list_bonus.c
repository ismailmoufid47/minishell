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

t_list	*extract_args_and_remove_them(t_list *head)
{
	t_list	*cur;
	t_list	*tmp;
	t_list	*tmp2;
	char	**args;

	cur = head;
	while (cur)
	{
		if (cur->type == CMD)
		{
			if (cur == head)
				head = ((args = match_wild_card(&cur)), cur);
			else
				args = match_wild_card(&cur);
			cur->args = args;
			tmp = cur->next;
			while (tmp && tmp->type == CMD)
				tmp = ((tmp2 = tmp->next), (free(tmp)), tmp2);
			cur->next = tmp;
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
