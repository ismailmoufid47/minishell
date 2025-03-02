/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:07:34 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/01 19:01:53 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int count_tokens(char *cmd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			if ((cmd[i] == '|' && cmd[i] == cmd[i + 1]) || (cmd[i] == '&' && cmd[i] == cmd[i + 1]))
			{
				count++;
				i += 2;
			}
			if (cmd[i] == '(' || cmd[i] == ')' || cmd[i] == '|' || cmd[i] == '&' || cmd[i] == ';')
			{
				count++;
				i++;
			}
			if (cmd[i] && cmd[i] != ' ')
			{
				count++;
				while (cmd[i] != ' ' && cmd[i] != '(' && cmd[i] != ')' && cmd[i] != '|' && cmd[i] != '&' && cmd[i] != ';')
					i++;
			}
		}
		if (cmd[i] == ' ')
			i++;
	}
	return (count);
}

char **fill_tokens(char **tokens, char *cmd)
{
	int i;
	int count;
	char c;
	int cmd_len;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			if ((cmd[i] == '|' && cmd[i] == cmd[i + 1]) || (cmd[i] == '&' && cmd[i] == cmd[i + 1]))
			{
				tokens[count] = malloc(3);
				ft_strlcpy(tokens[count], cmd + i, 3);
				count++;
				i += 2;
			}
			if (cmd[i] == '(' || cmd[i] == ')' || cmd[i] == '|' || cmd[i] == '&' || cmd[i] == ';')
			{
				tokens[count] = malloc(2);
				ft_strlcpy(tokens[count], cmd + i, 2);
				count++;
				i++;
			}
			if (cmd[i] && cmd[i] != ' ')
			{
				cmd_len = i;
				while (cmd[i] != ' ' && cmd[i] != '(' && cmd[i] != ')' && cmd[i] != '|' && cmd[i] != '&' && cmd[i] != ';')
					i++;
				cmd_len = i - cmd_len;
				tokens[count] = malloc(cmd_len + 1);
				ft_strlcpy(tokens[count], cmd + i - cmd_len, cmd_len + 1);
				count++;
			}
		}
		if (cmd[i] == ' ')
			i++;
	}
	tokens[count] = NULL;
	return (tokens);
}

char **tokenize(char *cmd)
{
	int	token_number;
	char	**tokens;

	token_number = count_tokens(cmd);
	tokens = malloc((token_number + 1) * sizeof(char *));
	tokens = fill_tokens(tokens, cmd);

}

t_ast *parse(char *cmd_line)
{
	char	**tokens;

	cmd_line = expand_env_variable(cmd_line);
	tokens = tokenize(cmd_line);
}

int main()
{
	char	*input;

	while (1)
	{
		input = readline(get_prompt());
		if (input == NULL)
			exit(0);
		print_tree(parse(input));
	}
	return (0);
}
