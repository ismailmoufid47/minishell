#include "../include/shell.h"

// int	get_token_count(char *input)
// {
// 	int	i;
// 	int	token_count;
// 	int	sq_flag;
// 	int	dq_flag;
// 	int	broke_for_special;

// 	i = 0;
// 	sq_flag = ((token_count = 0), (broke_for_special = 1), (dq_flag = 0), 0);
// 	while (input[i])
// 	{
// 		if (is_special_token(&input[i]) && !sq_flag && !dq_flag)
// 		{
// 			if (broke_for_special)
// 				token_count++;
// 			i++;
// 			if (input[i] == input[i - 1])
// 				i++;
// 		}
// 		broke_for_special = 0;
// 		while (input[i] == ' ')
// 			i++;
// 		if (!input[i])
// 			break ;
// 		token_count++;
// 		while (input[i] && (sq_flag || dq_flag || input[i] != ' '))
// 		{
// 			if (input[i] == '\'' && !dq_flag)
// 				sq_flag = !sq_flag;
// 			else if (input[i] == '"' && !sq_flag)
// 				dq_flag = !dq_flag;
// 			if (is_special_token(&input[i]) && !sq_flag && !dq_flag)
// 				break ;
// 			broke_for_special = 1;
// 			i++;
// 		}
// 	}
// 	return (token_count);
// }
int	get_token_count(char *input)
{
	int	i;
	int	count;
	int	sq_flag;
	int	dq_flag;
	int	in_token;

	sq_flag = ((in_token = 0), (i = 0), (count = 0), (dq_flag = 0), 0);
	while (input[i])
	{
		if (!in_token)
			count++;
		while (input[i] == ' ' && !sq_flag && !dq_flag)
			i = ((in_token = 0), i + 1);
		if (input[i] && is_special_token(&input[i]) && !sq_flag && !dq_flag)
			i = ((in_token = 0), i + 1 + (input[i] == input[i + 1]));
		if (input[i] && !in_token)
			in_token = ((count++), 1);
		if (input[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if (input[i] == '"' && !sq_flag)
			dq_flag = !dq_flag;
		if (input[i])
			i++;
	}
	return (count);
}


int	get_token_length(char *input, int *i)
{
	int	start;
	int	sq_flag;
	int	dq_flag;

	start = *i;
	sq_flag = ((dq_flag = 0), 0);
	if (is_special_token(input + *i))
	{
		(*i)++;
		if (input[*i] == input[*i -1])
		{
			(*i)++;
			return (2);
		}
		return (1);
	}
	while (input[*i])
	{
		if (input[*i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if (input[*i] == '"' && !sq_flag)
			dq_flag = !dq_flag;
		else if (!sq_flag && !dq_flag && input[*i] == ' ')
			break ;
		if (!sq_flag && !dq_flag && is_special_token(input + *i))
			break ;
		(*i)++;
	}
	return (*i - start);
}

char	*allocate_token(char *input, int start, int length)
{
	char	*token;
	int		sq_flag;
	int		dq_flag;
	int		j;
	int		i;

	token = malloc(length + 1);
	j = 0;
	i = start;
	sq_flag = ((dq_flag = 0), 0);
	if (!token)
		return (NULL);
	if (input[start] == '"' || input[start] == '\'')
	{
		token[j] = input[start];
		if (input[start] == '\'')
			sq_flag = 1;
		else
			dq_flag = 1;
		i++;
		j++;
	}
	while (i < start + length)
	{
		if (input[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if (input[i] == '"' && !sq_flag)
			dq_flag = !dq_flag;
		token[j] = 0;
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
