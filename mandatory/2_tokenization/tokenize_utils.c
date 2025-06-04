#include "../include/shell.h"

int	validate_tokens(char **tokens, t_envp *envp)
{
	int		i;

	i = 0;
	if (tokens[0] && !ft_strcmp(tokens[0], "|"))
		return (syntax_error(tokens, "|", envp));
	while (tokens[i])
	{
		if (is_special_token(tokens[i]) && !tokens[i + 1])
			return (syntax_error(tokens, "newline", envp));
		if (ft_strcmp(tokens[i], "|") && is_special_token(tokens[i])
			&& is_special_token(tokens[i + 1]))
			return (syntax_error(tokens, tokens[i + 1], envp));
		i++;
	}
	return (1);
}

int	is_special_token(char *token)
{
	return (is_special_operator(token[0]) || is_double_symbol(token, 0));
}

int	is_double_symbol(char *input, int pos)
{
	if (!input[pos] || !input[pos + 1])
		return (0);
	return ((input[pos] == '<' && input[pos + 1] == '<')
		|| (input[pos] == '>' && input[pos + 1] == '>'));
}

int	is_special_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	skip_quoted_section(char *input, int *pos, char quote)
{
	(*pos)++;
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	if (input[*pos] == quote)
		(*pos)++;
}
