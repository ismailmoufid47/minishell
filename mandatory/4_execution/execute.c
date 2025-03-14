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
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT, 0666), 1);
		if (current->type == APP)
			ft_dup2(open_wrapper(file, O_WRONLY | O_CREAT | O_APPEND, 0666), 1);
		if (current->type == HDOC)
			handle_here_doc(file);
		current = current->next->next;
	}
}


char	**envp_to_char(t_envp *envp)
{
	int		count;
	t_envp	*current;
	char	**result;
	char	*tmp;

	count = 0;
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
	result[count] = NULL;
	return (result);
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

char	**split_zayda_naghza(char *full_cmd)
{
	int		i;
	char	**tokens;

	i = 0;
	tokens = tokenize(full_cmd);
	while (tokens[i])
	{
		if (tokens[i][0] == '\'' || tokens[i][0] == '"')
		{
			if (tokens[i][0] == tokens[i][ft_strlen(tokens[i]) - 1])
				tokens[i][ft_strlen(tokens[i]) - 1] = 0;
			tokens[i] = &tokens[i][1];
		}
		i++;
	}
	return (tokens);
}

int	is_built_in(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "pwd"));
}

void	execute_cmd(t_list *cmd, t_envp *envp, t_list *prev)
{
	char	**envp_char;
	char	*cmd_path;
	char	**args;

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
		redirect(cmd->redirections);
	envp_char = envp_to_char(envp);
	args = split_zayda_naghza(cmd->value);
	if (is_built_in(args[0]))
		cmd_path = ft_strjoin("./bin/", args[0]);
	else
		cmd_path = get_cmd_path(args[0], envp_char);
	if (cmd_path)
		execve(cmd_path, args, envp_char);
	error(args[0]);
}

void	execute(t_list *list, t_envp *envp)
{
	t_list	*current;
	t_list	*prev;
	t_list	*prev_pipe;
	pid_t	pid;
	int		status;

	current = list;
	prev = NULL;
	prev_pipe = NULL;
	while (current)
	{
		if (current->type == PIPE && prev_pipe)
			close_2(prev_pipe->pipe_fds[0], prev_pipe->pipe_fds[1]);
		if (!ft_strncmp(current->value, "cd ", 3)
			|| !ft_strcmp(current->value, "cd"))
			cd(current->value, envp);
		if (!ft_strncmp(current->value, "export ", 7)
			|| !ft_strcmp(current->value, "export"))
			export(current->value, envp);
		else if (current->type == CMD)
		{
			pid = fork();
			if (pid == 0)
				execute_cmd(current, envp, prev);
			else if (pid == -1)
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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		free(envp->value);
		envp->value = ft_itoa(WEXITSTATUS(status));
	}
	while (wait(NULL) > 0)
		;
}
