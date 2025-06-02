#include "include/shell.h"

int	g_signal = 0;

// void	print_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	printf("\n		TOKENS\n\n");
// 	while (tokens[i])
// 	{
// 		printf("	%d: %s\n", i, tokens[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

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

int	set_cmd_here_doc(t_list *list, t_envp *envp)
{
	pid_t			pid;
	t_list			*current;
	static int		here_doc_count = 0;
	int				file_fd[2];
	char			*file_name;
	int				status;
	char			*tmp;
	struct termios	old;

	tcgetattr(STDIN_FILENO, &old);
	file_fd[0] = 0;
	current = list->redirections;
	while (current)
	{
		if (current->type == HDOC)
		{
			tmp = ft_itoa(here_doc_count);
			file_name = ft_strjoin("/tmp/.here_doc_", tmp);
			free(tmp);
			unlink(file_name);
			if (file_fd[0])
				close(file_fd[0]);
			file_fd[1] = open_wrapper(file_name, O_W | O_C | O_T, 0666);
			file_fd[0] = open_wrapper(file_name, O_RDONLY, 0);
			unlink(file_name);
			free(file_name);
			here_doc_count++;
			list->here_doc = file_fd[0];
			pid = fork_wrapper(envp);
			if (pid == 0)
				handle_here_doc(current->next, envp, file_fd[1]);
			else
			{
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
				tcsetattr(STDIN_FILENO, TCSANOW, &old);
				signal(SIGINT, print_prompt);
				close(file_fd[1]);
				if (WIFEXITED(status))
				{
					free(envp->value);
					envp->value = ft_itoa(WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status))
				{
					free(envp->value);
					envp->value = ft_itoa(WTERMSIG(status) + 128);
					return (0);
				}
			}
		}
		current = current->next;
	}
	return (1);
}

int	handle_here_docs(t_envp *envp, t_list *list)
{
	while (list)
	{
		if (list->type == CMD && list->is_redirected)
		{
			if (!set_cmd_here_doc(list, envp))
				return (0);
		}
		list = list->next;
	}
	return (1);
}

t_list	*parse(char *cmd_line, t_envp *envp)
{
	char	**tokens;
	t_list	*list;

	list = NULL;
	cmd_line = expand_env_variable(cmd_line, envp, 0);
	if (!cmd_line || !*cmd_line)
	{
		free(cmd_line);
		return (NULL);
	}
	//printf("\nCMDLINE AFTER EXPANSION: %s\n\n", cmd_line);
	tokens = tokenize(cmd_line);
	free(cmd_line);
	if (!validate_tokens(tokens, envp))
		return (NULL);
	// print_tokens(tokens);
	list = create_list(tokens);
	free(tokens);
	// print_list(list, 0);
	if (!handle_here_docs(envp, list))
		return (free_list(list), NULL);
	return (list);
}

int	main(void)
{
	char	*cmd_line;
	t_list	*list;
	int		history_fd;
	t_envp	*envp;
	char	*prompt;
	int		re;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, print_prompt);
	rl_catch_signals = 0;
	envp = set_envp();
	if (ft_get_env_val(envp, "HOME"))
		cmd_line = ft_strjoin(ft_get_env_val(envp, "HOME"), "/.bash_history");
	else
		cmd_line = ft_strdup("/tmp/.bash_history");
	history_fd = open_wrapper(cmd_line, O_RDWR | O_CREAT | O_APPEND, 0666);
	load_history(history_fd);
	free(cmd_line);
	while (1)
	{
		prompt = get_prompt(envp);
		cmd_line = readline(prompt);
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			free(envp->value);
			envp->value = ft_strdup("1");
		}
		free(prompt);
		if (cmd_line == NULL)
		{
			re = ft_atoi(ft_get_env_val(envp, "?"));
			free_envp(envp);
			return (printf("exit\n"), re);
		}
		if (*cmd_line == 0)
		{
			free(cmd_line);
			continue ;
		}
		if (*cmd_line)
		{
			add_history(cmd_line);
			write(history_fd, cmd_line, strlen(cmd_line));
			write(history_fd, "\n", 1);
		}
		list = parse(cmd_line, envp);
		if (list)
			execute(list, &envp);
		free_list(list);
	}
	close(history_fd);
	return (0);
}
