/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   shell.c                                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

int	g_signal = 0;

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("\n		TOKENS\n\n");
	while (tokens[i])
	{
		printf("	%d: %s\n", i, tokens[i]);
		i++;
	}
	printf("\n");
}


void	print_list(t_list *list, int tab_count)
{
	int	i;

	i = 0;
	if (tab_count == 0)
	{
		printf("\n");
		while (i++ < tab_count)
			printf("		");
		printf("		LIST\n\n");
	}
	while (list)
	{
		i = 0;
		while (i++ < tab_count)
			printf("		");
		if (list->type == HDOC)
			printf("      HEREDOC");
		else if (list->type == APP)
			printf("       APPEND");
		else if (list->type == IN)
			printf("	 IN");
		else if (list->type == OUT)
			printf("	 OUT");
		else if (list->type == PIPE)
		{
			printf("       PIPE  FDS:\n");
			printf("		IN:%d\n", list->pipe_fds[0]);
			printf("		OUT:%d\n", list->pipe_fds[1]);
		}
		else if (list->type == FIL)
			printf("      FILE: %s, quote: %d", list->value, list->quote_type);
		else
		{
			printf("       CMD:  %s, quote: %d", list->value, list->quote_type);
			if (list->redirected)
			{
				printf(",  REDIRECTIONS:\n");
				print_list(list->redirs, tab_count + 1);
			}
			printf(" args: \n");
			print_tokens(list->args);
		}
		list = list->next;
		if (list)
		{
			i = 0;
			printf("\n");
			while (i++ < tab_count)
				printf("		");
			printf("	  ↓\n");
		}
	}
	printf("\n\n");
}

t_list	*parse(char *cmd_line, t_envp *envp)
{
	char	**tokens;
	t_list	*list;

	list = NULL;
	cmd_line = expand_env_variable(cmd_line, envp);
	printf("%s\n", cmd_line);
	if (!cmd_line || !*cmd_line)
	{
		free(cmd_line);
		return (NULL);
	}
	tokens = tokenize(cmd_line);
	free(cmd_line);
	if (!validate_tokens(tokens, envp))
		return (NULL);
	list = create_list(NULL, NULL, tokens);
	print_list(list, 0);
	free(tokens);
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
		write(history_fd, *cmd_line, ft_strlen(*cmd_line));
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
			execute(list, envp);
		free_list(list);
	}
	return ((close(history_fd)), 0);
}
