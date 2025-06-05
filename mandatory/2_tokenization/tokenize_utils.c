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
	if (!token || !token[0])
		return (0);
	if (token[0] == '<' && token[1] == '<')
		return (1);
	if (token[0] == '>' && token[1] == '>')
		return (1);
	return (token[0] == '<' || token[0] == '>' || token[0] == '|');
}

int	is_single_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}


void	update_quote_flags(char c, int *sq_flag, int *dq_flag)
{
	if (c == '\'' && !(*dq_flag))
		*sq_flag = !(*sq_flag);
	else if (c == '"' && !(*sq_flag))
		*dq_flag = !(*dq_flag);
}

int	handle_special_token(const char *input, int i, int *count, int *special)
{
	if (*special)
		(*count)++;
	i++;
	if (input[i] == input[i - 1])
		i++;
	*special = 0;
	return (i);
}
