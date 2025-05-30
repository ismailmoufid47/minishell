#include "../include/shell.h"

extern int	g_signal;

void	redirect(t_list *redirections, t_envp *envp, int stdin_fd)
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
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT, 0666), 1);
		if (current->type == APP)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT | O_APPEND, 0666), 1);
		if (current->type == HDOC)
		{
			dup2(stdin_fd, 0);
			handle_here_doc(file, envp);
		}
		current = current->next->next;
	}
	signal(SIGQUIT, SIG_DFL);
	close(stdin_fd);
}

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*cmd_path;
	char	*tmp;
	char	**path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (cmd && !access(cmd, X_OK))
			return (cmd);
		return (NULL);
	}
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		tmp = ft_strjoin(getcwd(NULL, 0), "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(cmd_path, X_OK))
		{
			return (cmd_path);
		}
		return (free(cmd_path), NULL);
	}
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
	ft_free_split(path);
	return (free(cmd_path), NULL);
}

void	execute_cmd(t_list *cmd, t_envp *envp, t_list *prev, int stdin_fd)
{
	char	**envp_char;
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
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
		redirect(cmd->redirections, envp, stdin_fd);
	if (cmd->value == NULL)
		exit (0);
	envp_char = envp_to_char(envp);
	if (is_bin(cmd->args[0]))
		cmd_path = ft_strjoin("/tmp/bin/", cmd->args[0]);
	else
		cmd_path = get_cmd_path(cmd->args[0], envp_char);
	if (cmd_path)
		execve(cmd_path, cmd->args, envp_char);
	exec_error(cmd->args[0]);
}

void	execute(t_list *list, t_envp **envp)
{
	t_list	*current;
	t_list	*prev;
	t_list	*prev_pipe;
	int		status;
	int		is_built_in;
	int 	stdin_fd;
	struct termios old;

	current = list;
	prev = NULL;
	prev_pipe = NULL;
	stdin_fd = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &old);
	while (current)
	{
		is_built_in = 1;
		if (current->type == PIPE && prev_pipe)
			close_2(prev_pipe->pipe_fds[0], prev_pipe->pipe_fds[1]);
		if (!ft_strcmp(current->value, "cd"))
			cd(current->args, *envp, current, prev);
		else if (!ft_strcmp(current->value, "export"))
			export(current->args, *envp, current, prev);
		else if (!ft_strcmp(current->value, "unset"))
			unset(current->args, *envp, current, prev);
		else if (!ft_strcmp(current->value, "exit"))
			exit_cmd(current->args, *envp, current, prev);
		else if (current->type == CMD)
		{
			is_built_in = 0;
			current->pid = fork();
			if (current->pid == 0)
				execute_cmd(current, (*envp), prev, stdin_fd);
			else if (current->pid == -1)
			{
				error_fork(&(*envp), ft_strdup("fork"));
				break ;
			}
		}
		prev = current;
		if (current->type == PIPE)
			prev_pipe = current;
		current = current->next;
	}
	close(stdin_fd);
	if (prev_pipe)
		close_2(prev_pipe->pipe_fds[1], prev_pipe->pipe_fds[1]);
	while (list)
	{
		if (list->type == PIPE)
			close_2(list->pipe_fds[0], list->pipe_fds[1]);
		list = list->next;
	}
	signal(SIGINT, SIG_IGN);
	waitpid(prev->pid, &status, 0);
	g_signal = 0;
	if (is_built_in)
		;
	else if (WIFEXITED(status))
	{
		free((*envp)->value);
		(*envp)->value = ft_itoa(WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		(*envp)->value = ft_itoa(WTERMSIG(status) + 128) ;
		g_signal = -1;
	}
	while (wait(NULL) > 0)
		;
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	signal(SIGINT, print_prompt);
}
