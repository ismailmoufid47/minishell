/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   here_doc_handler_bonus.c                            :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

void	handle_here_doc(t_list *file, t_envp *envp, int out)
{
	char	*input;
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	input = "NULL";
	tmp = readline("> ");
	while (tmp && ft_strcmp(tmp, file->value))
	{
		input = tmp;
		if (file->quote_type == UNQUOTED)
			input = expand_env_variable(tmp, envp, 1);
		ft_putendl_fd(input, out);
		free(input);
		tmp = readline("> ");
	}
	if (!tmp)
		exit(1);
	free(tmp);
	exit (0);
}

void	create_heredoc_file(int *here_doc_count, int (*file_fd)[2])
{
	char	*file_name;
	char	*tmp;

	tmp = ft_itoa(*here_doc_count);
	file_name = ft_strjoin("/tmp/.here_doc_", tmp);
	free(tmp);
	unlink(file_name);
	if ((*file_fd)[0])
		close((*file_fd)[0]);
	(*file_fd)[1] = open_wrapper(file_name, O_W | O_C | O_T, 0666);
	(*file_fd)[0] = open_wrapper(file_name, O_RDONLY, 0);
	unlink(file_name);
	free(file_name);
	(*here_doc_count)++;
}

int	parent_heredoc(t_envp *envp, pid_t pid, int heredoc_out, t_term *old)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, old);
	signal(SIGINT, print_prompt);
	close(heredoc_out);
	free(envp->value);
	if (WIFEXITED(status))
		envp->value = (ft_itoa(WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
		return (envp->value = ft_itoa(WTERMSIG(status) + 128), 0);
	return (1);
}

int	set_cmd_here_doc(t_list *list, t_envp *envp)
{
	pid_t			pid;
	t_list			*current;
	static int		here_doc_count = 0;
	int				file_fd[2];
	t_term			old;

	tcgetattr(STDIN_FILENO, &old);
	file_fd[0] = 0;
	current = list->redirs;
	while (current)
	{
		if (current->type == HDOC)
		{
			create_heredoc_file(&here_doc_count, &file_fd);
			list->here_doc = file_fd[0];
			pid = fork_wrapper(envp);
			if (pid == 0)
				handle_here_doc(current->next, envp, file_fd[1]);
			else if (!parent_heredoc(envp, pid, file_fd[1], &old))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	handle_here_docs(t_envp *envp, t_list *list)
{
	while (list)
	{
		if (list->type == CMD && list->redirected)
		{
			if (!set_cmd_here_doc(list, envp))
				return (0);
		}
		list = list->next;
	}
	return (1);
}
