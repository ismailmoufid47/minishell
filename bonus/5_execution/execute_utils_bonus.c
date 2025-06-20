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

#include "../include/shell_bonus.h"

char	**match_files(char *file)
{
	char	**files;

	files = match_wild_card(tokens_to_list(ft_split(file, '\x81')));
	if (files[1])
	{
		ft_free_split(files);
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Ambiguous redirect", 2);
		exit(1);
	}
	return (files);
}

void	builtin_here_doc(char *delimiter, t_envp *envp)
{
	int		fd1;
	int		fd2;
	char	*input;
	char	*tmp;

	fd1 = open_wrapper("read_line", O_W | O_C | O_T, 0600);
	fd2 = ((input = "NULL"), open_wrapper("read_line", O_RDONLY, 0));
	unlink("read_line");
	tmp = readline("> ");
	while (tmp && ft_strcmp(tmp, delimiter))
	{
		input = expand_env_variable(tmp, envp, 0);
		ft_putendl_fd(input, fd1);
		free(tmp);
		free(input);
		tmp = readline("> ");
	}
	if (!input)
	{
		close_2(fd1, fd2);
		ft_putendl_fd("Minishell: here_doc:  EOF - CTL + D", 2);
		exit(1);
	}
	free(tmp);
	close(fd1);
}

void	execute_builtin(t_list *current, t_envp *envp, t_list *prev, int *built)
{
	*built = 1;
	if (current->type == CMD && current->value)
	{
		current->args = match_wild_card(tokens_to_list(current->args));
		current->value = current->args[0];
	}
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
