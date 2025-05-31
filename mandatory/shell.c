/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:50:44 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/31 16:47:08 by isel-mou         ###   ########.fr       */
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

t_list	*parse(char *cmd_line, t_envp *envp)
{
	char	**tokens;
	t_list	*list;

	list = NULL;
	cmd_line = expand_env_variable(cmd_line, envp);
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
	return (list);
}

int	main(void)
{
	char	*cmd_line;
	t_list	*list;
	int		history_fd;
	t_envp	*envp;
	char	*prompt;

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
			int re = ft_atoi(ft_get_env_val(envp, "?"));
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
