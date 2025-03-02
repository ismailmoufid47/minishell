/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:07:34 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/02 16:03:22 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void print_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

t_ast	*parse(char *cmd_line)
{
	char	**tokens;
	t_ast	*root;

	root = NULL;
	cmd_line = expand_env_variable(cmd_line);
	tokens = tokenize(cmd_line);
	print_tokens(tokens);
	return (root);
}

int	main(void)
{
	char	*input;
	t_ast	*root;

	while (1)
	{
		input = readline(get_prompt());
		if (input == NULL)
			exit(0);
		root = parse(input);
		// print_tree(parse(input));
	}
	return (0);
}
