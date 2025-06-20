/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   wildcard_utils_bonus.c                              :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

t_list	*tokens_to_list(char **tokens)
{
	int		i;
	t_list	*nav;
	t_list	*head;

	if (!tokens || !tokens[0])
		return (NULL);
	head = create_list_node(tokens[0], CMD);
	head->value = ft_strdup(head->value);
	nav = head;
	i = 0;
	while (tokens[++i])
	{
		nav->next = create_list_node(tokens[i], CMD);
		nav->next->value = ft_strdup(nav->next->value);
		nav = nav->next;
	}
	ft_free_split(tokens);
	return (head);
}

char	**list_to_char(t_list *list)
{
	int		count;
	t_list	*current;
	char	**result;

	count = 0;
	current = list;
	while (current)
	{
		count++;
		current = current->next;
	}
	result = malloc((count + 1) * sizeof(char *));
	count = 0;
	while (list)
	{
		result[count] = list->value;
		current = list;
		list = list->next;
		count++;
	}
	result[count] = NULL;
	return (result);
}

t_list	*link_matchs(t_list *head, t_list **prev, t_list **nav, t_list *matchs)
{
	t_list	*last;

	if (!matchs)
		return (head);
	if (!*prev)
	{
		last = head->next;
		free(head->value);
		free(head);
		head = matchs;
	}
	else
	{
		last = (*prev)->next->next;
		free((*prev)->next->value);
		free((*prev)->next);
		(*prev)->next = matchs;
	}
	while (matchs->next)
		matchs = matchs->next;
	matchs->next = last;
	*nav = matchs;
	return (head);
}
