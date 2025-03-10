#include "../include/shell.h"

int	is_special_token(char *token)
{
	return (is_double_symbol(token, 0) || is_special_operator(token[0]));
}

int	is_double_symbol(char *input, int pos)
{
	return ((input[pos] == '<' && input[pos + 1] == '<') || 
		(input[pos] == '>' && input[pos + 1] == '>'));
}

int	is_special_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	skip_whitespace(char *input, int *pos)
{
	while (input[*pos] == ' ')
		(*pos)++;
}

void	skip_quoted_section(char *input, int *pos, char quote)
{
	(*pos)++;
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	if (input[*pos] == quote)
		(*pos)++;
}
