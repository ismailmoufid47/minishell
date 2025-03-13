/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:50:44 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/12 21:51:29 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

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
	//printf("\nCMDLINE AFTER EXPANSION: %s\n\n", cmd_line);
	tokens = tokenize(cmd_line);
	if (!validate_tokens(tokens))
		return (NULL);
	print_tokens(tokens);
	list = create_list(tokens);
	print_list(list, 0);
	return (list);
}

int	main(void)
{
	char	*input;
	t_list	*list;
	int		history_fd;
	t_envp	*envp;
	char	*prompt;

	envp = set_envp();
	input = ft_strjoin(ft_get_env_val(envp, "HOME"), "/.bash_history");
	history_fd = open_wrapper(input, O_RDWR | O_CREAT | O_APPEND, 0666);
	load_history(history_fd);
	free(input);
	while (1)
	{
		prompt = get_prompt(envp);
		input = readline(prompt);
		free(prompt);
		if (input == NULL)
			exit(0);
		if (*input == 0)
			continue ;
		if (*input)
		{
			add_history(input);
			write(history_fd, input, strlen(input));
			write(history_fd, "\n", 1);
		}
		list = parse(input, envp);
		execute(list, envp);
		free(input);
	}
	close(history_fd);
	return (0);
}
