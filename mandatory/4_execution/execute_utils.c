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

int	check_ambiguous(char *src, char **files, t_list *list)
{
	if (files && ((!files[0] || files[1]) || files[0][0] == 0))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(src, 2);
		ft_free_split(files);
		ft_putendl_fd(": Ambiguous redirect", 2);
		if (list)
		{
			free_list(list);
			exit(1);
		}
		return (1);
	}
	return (0);
}

void	expand_files(t_list *file, char ***files, t_envp *envp, t_list *current)
{
	char	*duplicate;
	char	*tmp;

	duplicate = ft_strdup(file->value);
	if (file->quote_type != SIQUOTED && current->type != HDOC)
	{
		tmp = expand_env_variable(file->value, envp);
		if (file->quote_type == DOQUOTED)
			return (*files = (char_to_double_char(tmp)),
				(file->value = duplicate), (free(tmp)), (void)0);
		*files = tokenize(tmp);
		free(tmp);
		if ((*files)[0] && (*files)[0][0] == '"')
		{
			tmp = ft_strdup((*files)[0] + 1);
			free((*files)[0]);
			(*files)[0] = tmp;
		}
		file->value = duplicate;
	}
	else
		*files = ((free(duplicate)), char_to_double_char(file->value));
}
