#include "../include/shell.h"

int	token_count(char *input)
{
	int	i;
	int	count;
	int	sq_flag;
	int	dq_flag;
	int	special;

	special = ((i = 0), (count = 0), (sq_flag = 0), (dq_flag = 0), 1);
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (input[i] && is_special_token(&input[i]) && !sq_flag && !dq_flag)
			i = handle_special_token(input, i, &count, &special);
		else
		{
			special = ((count++), 0);
			while (input[i] && !(!sq_flag && !dq_flag && input[i] == ' '))
			{
				update_quote_flags(input[i], &sq_flag, &dq_flag);
				if (is_special_token(&input[i]) && !sq_flag && !dq_flag)
					break ;
				special = ((i++), 1);
			}
		}
	}
	return (count);
}


int	token_length(char *input, int *i)
{
	int	start;
	int	sq_flag;
	int	dq_flag;

	sq_flag = ((start = *i), (dq_flag = 0), 0);
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
		update_quote_flags(input[*i], &sq_flag, &dq_flag);
		if ((!sq_flag && !dq_flag && input[*i] == ' ')
			|| (!sq_flag && !dq_flag && is_special_token(input + *i)))
			break ;
		(*i)++;
	}
	return (*i - start);
}

char	*allocate_token(char *input, int start, int lgth)
{
	char	*tok;
	int		sq_flg;
	int		dq_flg;
	int		j;
	int		i;

	sq_flg = ((tok = malloc(lgth + 1)), (j = 0), (i = start), (dq_flg = 0), 0);
	if (!tok)
		return (NULL);
	if (input[start] == '"' || input[start] == '\'')
	{
		tok[j] = input[start];
		update_quote_flags(input[start], &sq_flg, &dq_flg);
		i = ((j++), 1 + 1);
	}
	while (i < start + lgth)
	{
		update_quote_flags(input[i], &sq_flg, &dq_flg);
		tok[j] = 0;
		if ((input[i] != '\'' && input[i] != '"')
			|| (input[i] == '\'' && dq_flg) || (input[i] == '"' && sq_flg))
			tok[j++] = input[i];
		i++;
	}
	return ((tok[j] = '\0'), tok);
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
		length = token_length(input, &i);
		tokens[j++] = allocate_token(input, start, length);
	}
	tokens[j] = NULL;
	return (tokens);
}

char	**tokenize(char *input)
{
	int		count;
	char	**tokens;

	count = token_count(input);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	return (extract_tokens(tokens, input));
}
