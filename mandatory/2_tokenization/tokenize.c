#include "../include/shell.h"

int	get_token_count2(char *input)
{
	int	i;
	int	token_count;

	i = ((token_count = 0), 0);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		token_count++;
		if (input[i] == '"' || input[i] == '\'')
			skip_quoted_section(input, &i, input[i]);
		else if (is_double_symbol(input, i))
			i += 2;
		else if (is_special_operator(input[i]))
			i++;
		else
		{
			while (input[i]
				&& !is_special_operator(input[i]) && !ft_isspace(input[i]))
				i++;
		}
	}
	return (token_count);
}
int	get_token_count(char *input)
{
	int	i;
	int	token_count;
	int	sq_flag;
	int	dq_flag;

	i = 0;
	token_count = 0;
	sq_flag = 0;
	dq_flag = 0;

	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		token_count++;
		while (input[i] && (sq_flag || dq_flag || input[i] != ' '))
		{
			if (input[i] == '\'' && !dq_flag)
				sq_flag = !sq_flag;
			else if (input[i] == '"' && !sq_flag)
				dq_flag = !dq_flag;
			i++;
		}
	}
	return (token_count);
}

int	get_token_length(char *input, int *i)
{
	int	start;

	start = *i;
	if (input[*i] == '"' || input[*i] == '\'')
		skip_quoted_section(input, i, input[*i]);
	else if (is_double_symbol(input, *i))
		*i += 2;
	else if (is_special_operator(input[*i]))
		(*i)++;
	else
	{
		while (input[*i]
			&& !is_special_operator(input[*i]) && !ft_isspace(input[*i]))
			(*i)++;
	}
	return (*i - start);
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
	int	i;
	int	token_index;
	int	length;

	i = ((token_index = 0), 0);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		length = get_token_length(input, &i);
		tokens[token_index] = allocate_token(input, i - length, length);
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
