#include "../include/shell.h"

int	get_token_count(char *input)
{
	int	i;
	int	token_count;
	int	sq_flag;
	int	dq_flag;

	i = 0;
	token_count = 0;
	sq_flag = ((dq_flag = 0), 0);
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
	int	sq_flag;
	int	dq_flag;

	start = *i;
	sq_flag = ((dq_flag = 0), 0);
	while (input[*i])
	{
		if (input[*i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if (input[*i] == '"' && !sq_flag)
			dq_flag = !dq_flag;
		else if (!sq_flag && !dq_flag && input[*i] == ' ')
			break ;
		(*i)++;
	}
	return (*i - start);
}

char	*allocate_token(char *input, int start, int length)
{
	char	*token;
	int	sq_flag;
	int	dq_flag;
	int		j;
	int		i;

	token = malloc(length + 1);
	j = 0;
	i = start;
	sq_flag = ((dq_flag = 0), 0);
	if (!token)
		return (NULL);
	while (i < start + length)
	{
		if (input[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if (input[i] == '"' && !sq_flag)
			dq_flag = !dq_flag;
		if (input[i] == '\'' && dq_flag)
			token[j++] = input[i];
		if (input[i] == '"' && sq_flag)
			token[j++] = input[i];
		if (input[i] != '\'' && input[i] != '"')
			token[j++] = input[i];
		i++;
	}
	token[j] = '\0';
	return (token);
}

char	**extract_tokens(char **tokens, char *input)
{
	int	i;
	int	j;
	int	start;
	int	length;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		start = i;
		length = get_token_length(input, &i);
		tokens[j++] = allocate_token(input, start, length);
	}
	tokens[j] = NULL;
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
