#include "../include/shell.h"

void	redirect(t_list *redirections)
{
	t_list	*current;
	char	*file;

	current = redirections;
	while (current)
	{
		file = current->next->value;
		if (current->type == IN)
			ft_dup2(open_wrapper(file, O_RDONLY, 0), 0);
		if (current->type == OUT)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT, 0200), 0);
		if (current->type == APP)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT | O_APPEND, 0200), 0);
		if (current->type == HDOC)
			handle_here_doc(file);
		current = current->next->next;
	}
}

void	pipe_wrapper(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		error(ft_strdup("pipe"));
}

char	**envp_to_char(t_envp *envp)
{
	int		count;
	t_envp	*current;
	char	**result;
	char	*tmp;

	current = envp;
	while (current)
	{
		count++;
		current->next;
	}
	result = malloc((count + 1) * sizeof(char *));
	count = 0;
	while (envp)
	{
		tmp = ft_strjoin(envp->name, "=");
		result[count] = ft_strjoin(tmp, envp->value);
		free(tmp);
		count++;
		envp = envp->next;
	}
	return (result);
}

void	execute_cmd(t_list *cmd, t_envp *envp)
{
	char	**envp_char;
	char	**args;

	if (cmd->is_redirected)
		redirect(cmd->redirections);
	envp_char = envp_to_char(envp);
	args = ft_split(cmd->value);

}

void	execute(t_list *list, t_envp *envp)
{
	t_list	*current;
	int		pipe_fd[2];
	int		pid;

	current = list;
	while (current)
	{
		if (current->next && current->next->type == PIPE)
		{
			pipe_wrapper(pipe_fd);
			ft_dup2(pipe_fd[1], STDOUT_FILENO);
			pid = fork();
			if (pid == 0)
				execute_cmd(current, envp);
		}
		current = current->next;
	}
}
