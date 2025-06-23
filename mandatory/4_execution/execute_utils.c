/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   execute_utils.c                                     :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"


void	execute_builtin(t_list *current, t_envp *envp, t_list *prev, int *built)
{
	*built = 1;
	if (!ft_strcmp(current->value, "cd"))
		cd(current->args, envp, current, prev);
	else if (!prev && !current->next && !ft_strcmp(current->value, "export"))
		export(current->args, envp, current, prev);
	else if (!ft_strcmp(current->value, "unset"))
		unset(current->args, envp, current, prev);
	else if (!ft_strcmp(current->value, "exit"))
		exit_cmd(current->args, envp, current, prev);
	else
		*built = 0;
}

void	close_obsolete_fds(t_list *current, t_list *prev)
{
	if (current->here_doc)
		close(current->here_doc);
	if (prev)
		close(prev->pipe_fds[0]);
	if (current->next)
		close(current->next->pipe_fds[1]);
}
