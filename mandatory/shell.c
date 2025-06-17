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

int	handle_cmdline(t_envp *envp, int history_fd, char **cmd_line)
{
	char	*prompt;
	int		re;

	prompt = get_prompt(envp);
	*cmd_line = readline(prompt);
	if (g_signal == SIGINT)
		envp->value = ((g_signal = 0), (free(envp->value)), ft_strdup("1"));
	free(prompt);
	if (!*cmd_line)
	{
		re = ft_atoi(ft_get_env_val(envp, "?"));
		free_envp(envp);
		printf("exit\n");
		close(history_fd);
		exit(re);
	}
	if (!**cmd_line)
		return (free(*cmd_line), 0);
	if (**cmd_line)
	{
		add_history(*cmd_line);
		write(history_fd, *cmd_line, strlen(*cmd_line));
		write(history_fd, "\n", 1);
	}
	return (1);
}

int	main(void)
{
	t_list	*list;
	int		history_fd;
	t_envp	*envp;
	char	*cmd_line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, print_prompt);
	envp = ((rl_catch_signals = 0), set_envp());
	if (ft_get_env_val(envp, "HOME"))
		cmd_line = ft_strjoin(ft_get_env_val(envp, "HOME"), "/.bash_history");
	else
		cmd_line = ft_strdup("/tmp/.bash_history");
	history_fd = open_wrapper(cmd_line, O_RDWR | O_CREAT | O_APPEND, 0666);
	load_history(history_fd);
	free(cmd_line);
	while (1)
	{
		if (!handle_cmdline(envp, history_fd, &cmd_line))
			continue ;
		list = parse(cmd_line, envp);
		if (list)
			execute(list, &envp);
		free_list(list);
	}
	return ((close(history_fd)), 0);
}
