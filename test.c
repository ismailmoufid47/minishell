#include <stdlib.h>
#include "libft/include/libft.h"

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

#include <stdio.h>

int main()
{
	int i = 0;
	char **tokens = tokenize("(cmd1||cmd2) ; cmd3;");

	while (tokens[i])
	{
		printf("%i --> %s\n", i, tokens[i]);
		i++;
	}
}
