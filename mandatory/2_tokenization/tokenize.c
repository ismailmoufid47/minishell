#include "../include/shell.h"

int	get_token_count(char *input)
{
	int	pos;
	int	token_count;

	pos = ((token_count = 0), 0);
	while (input[pos])
	{
		while (input[pos] == ' ')
			pos++;
		if (!input[pos])
			break ;
		token_count++;
		if (input[pos] == '"' || input[pos] == '\'')
			skip_quoted_section(input, &pos, input[pos]);
		else if (is_double_symbol(input, pos))
			pos += 2;
		else if (is_special_operator(input[pos]))
			pos++;
		else
		{
			while (input[pos]
				&& !is_special_operator(input[pos]) && !ft_isspace(input[pos]))
				pos++;
		}
	}
	return (token_count);
}

int	get_token_length(char *input, int *pos)
{
	int	start;

	start = *pos;
	if (input[*pos] == '"' || input[*pos] == '\'')
		skip_quoted_section(input, pos, input[*pos]);
	else if (is_double_symbol(input, *pos))
		*pos += 2;
	else if (is_special_operator(input[*pos]))
		(*pos)++;
	else
	{
		while (input[*pos]
			&& !is_special_operator(input[*pos]) && !ft_isspace(input[*pos]))
			(*pos)++;
	}
	return (*pos - start);
}

char	*allocate_token(char *input, int start, int length)
{
	char	*token;

	token = malloc(sizeof(char) * (length + 1));
	if (!token)
		return (NULL);
	ft_strlcpy(token, input + start, length + 1);
	return (token);
}

char	**extract_tokens(char **tokens, char *input)
{
	int	pos;
	int	token_index;
	int	length;

	pos = ((token_index = 0), 0);
	while (input[pos])
	{
		while (input[pos] == ' ')
			pos++;
		if (!input[pos])
			break ;
		length = get_token_length(input, &pos);
		tokens[token_index] = allocate_token(input, pos - length, length);
		if (!tokens[token_index])
			return (NULL);
		token_index++;
	}
	tokens[token_index] = NULL;
	return (tokens);
}

char	**tokenize(char *input)
{
	int		token_count;
	char	**tokens;

	token_count = get_token_count(input);
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	return (extract_tokens(tokens, input));
}
