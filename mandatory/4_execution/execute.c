#include "../include/shell.h"

void	redirect(t_list *redirections, t_envp *envp)
{
	t_list	*current;
	int		in;
	char	*file;

	current = redirections;
	in = dup(0);
	while (current)
	{
		file = current->next->value;
		if (current->type == IN)
			ft_dup2(open_wrapper(file, O_RDONLY, 0), 0);
		if (current->type == OUT)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT, 0666), 1);
		if (current->type == APP)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT | O_APPEND, 0666), 1);
		if (current->type == HDOC)
		{
			dup2(in, 0);
			handle_here_doc(file, envp);
		}
		current = current->next->next;
	}
	close(in);
}

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*cmd_path;
	char	**path;
	int		i;

	i = 0;
	if (cmd && !access(cmd, X_OK) && ft_strchr(cmd, '/'))
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

void	execute_cmd(t_list *cmd, t_envp *envp, t_list *prev)
{
	char	**envp_char;
	char	*cmd_path;

	signal(SIGINT, sig_int);
	if (prev)
	{
		ft_dup2(prev->pipe_fds[0], STDIN_FILENO);
		close(prev->pipe_fds[1]);
	}
	if (cmd->next)
	{
		ft_dup2(cmd->next->pipe_fds[1], STDOUT_FILENO);
		close(cmd->next->pipe_fds[0]);
	}
	if (cmd->is_redirected)
		redirect(cmd->redirections, envp);
	if (cmd->value == NULL)
		exit (0);
	envp_char = envp_to_char(envp);
	if (is_bin(cmd->args[0]))
		cmd_path = ft_strjoin("./bin/", cmd->args[0]);
	else
		cmd_path = get_cmd_path(cmd->args[0], envp_char);
	if (cmd_path)
		execve(cmd_path, cmd->args, envp_char);
	command_not_found(cmd->args[0]);
}

void	execute(t_list *list, t_envp *envp)
{
	t_list	*current;
	t_list	*prev;
	t_list	*prev_pipe;
	int		status;
	struct termios old;

	current = list;
	prev = NULL;
	prev_pipe = NULL;
	tcgetattr(STDIN_FILENO, &old);
	while (current)
	{
		if (current->type == PIPE && prev_pipe)
			close_2(prev_pipe->pipe_fds[0], prev_pipe->pipe_fds[1]);
		if (!ft_strcmp(current->value, "cd"))
			cd(current->args, envp);
		else if (!ft_strcmp(current->value, "export"))
			export(current->args, envp);
		else if (!ft_strcmp(current->value, "unset"))
			unset(current->args, envp);
		else if (!ft_strcmp(current->value, "exit"))
			exit_cmd(current->args, envp, list);
		else if (current->type == CMD)
		{
			current->pid = fork();
			if (current->pid == 0)
				execute_cmd(current, envp, prev);
			else if (current->pid == -1)
				error(ft_strdup("fork"));
		}
		prev = current;
		if (current->type == PIPE)
			prev_pipe = current;
		current = current->next;
	}
	if (prev_pipe)
		close_2(prev_pipe->pipe_fds[1], prev_pipe->pipe_fds[1]);
	while (list)
	{
		if (list->type == PIPE)
			close_2(list->pipe_fds[0], list->pipe_fds[1]);
		list = list->next;
	}
	waitpid(prev->pid, &status, 0);
	if (WIFEXITED(status))
	{
		free(envp->value);
		envp->value = ft_itoa(WEXITSTATUS(status));
	}
	while (wait(NULL) > 0)
		;
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
}
