/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   free_resources.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

void	free_envp(t_envp *envp)
{
	if (!envp)
		return ;
	free(envp->name);
	free(envp->value);
	free_envp(envp->next);
	return (free(envp));
}

void	free_list(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->type == CMD)
		{
			free(temp->cmd_path);
			ft_free_split(temp->args);
			if (temp->redirected)
				free_list(temp->redirs);
		}
		else
			free(temp->value);
		free(temp);
	}
}

void	free_pipes_hrdc_fds(t_list *list)
{
	while (list)
	{
		if (list->type == PIPE)
		{
			if (list->pipe_fds[0])
				close(list->pipe_fds[0]);
			if (list->pipe_fds[1])
				close(list->pipe_fds[1]);
		}
		if (list->type == CMD)
		{
			if (list->here_doc)
				close(list->here_doc);
		}
		list = list->next;
	}
}
