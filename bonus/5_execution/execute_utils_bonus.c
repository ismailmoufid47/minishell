/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   execute_utils_bonus.c                               :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

char	**match_files(t_list *file)
{
	char	**files;
	t_list	*list;

	if (file->quote_type != UNQUOTED)
		return (ft_split(file->value, '\x81'));
	list = tokens_to_list(ft_split(file->value, '\x81'));
	files = match_wild_card(&list);
	if (files[1])
	{
		ft_free_split(files);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file->value, 2);
		free_list(list);
		ft_putendl_fd(": Ambiguous redirect", 2);
		exit(1);
	}
	free_list(list);
	return (files);
}

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
