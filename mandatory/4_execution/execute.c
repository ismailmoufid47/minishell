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
		current = current->next;
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

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*cmd_path;
	char	**path;
	int		i;

	i = 0;
	if (cmd && !access(cmd, X_OK) && strchr(cmd, '/'))
		return (cmd);
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	i = ((path = ft_split(envp[i] + 5, ':')), 0);
	while (path[i++])
	{
		path[i - 1] = ((cmd_path = path[i - 1]), ft_strjoin(path[i - 1], "/"));
		free(cmd_path);
	}
	i = 0;
	cmd_path = ft_strjoin(path[i], cmd);
	while (path[i] && cmd_path && access(cmd_path, X_OK))
		cmd_path = ((free(cmd_path)), ft_strjoin(path[i++], cmd));
	if (cmd_path && !access(cmd_path, X_OK))
		return (cmd_path);
	return (free(cmd_path), (ft_free_split(path)), NULL);
}

void	execute_cmd(t_list *cmd, t_envp *envp)
{
	char	**envp_char;
	char	*cmd_path;
	char	**args;

	if (cmd->is_redirected)
		redirect(cmd->redirections);
	envp_char = envp_to_char(envp);
	args = ft_split(cmd->value, ' ');
	cmd_path = get_cmd_path(cmd->value, envp_char);
	execve(cmd_path, args, envp_char);
	error(ft_strdup(args[0]));

}

void	execute(t_list *list, t_envp *envp)
{
	t_list	*current;
	int		pipe_fd[2];
	int		pid;

	current = list;
	while (current)
	{
		if (current->type == CMD)
		{
			if (current->next && current->next->type == PIPE)
			{
				pipe_wrapper(pipe_fd);
				ft_dup2(pipe_fd[1], STDOUT_FILENO);
				pid = fork();
				if (pid == 0)
					execute_cmd(current, envp);
				else if (pid > 0)
					ft_dup2(pipe_fd[0], STDIN_FILENO);
				else
					error(ft_strdup("fork"));
			}
			else
			{
				pid = fork();
				if (pid == 0)
					execute_cmd(current, envp);
				else if (pid == -1)
					error(ft_strdup("fork"));
			}
		}
		current = current->next;
	}
	if (pid > 0)
	{
		close(0);
		close(1);
	}
}
