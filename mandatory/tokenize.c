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
			if (cmd[i] == '\'')
			{
				count++;
				while (cmd[i] && cmd[i] != '\'')
					i++;
			}
			if ((cmd[i] == '<' && cmd[i] == cmd[i + 1]) || (cmd[i] == '>' && cmd[i] == cmd[i + 1]))
			{
				count++;
				i += 2;
			}
			if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
			{
				count++;
				i++;
			}
			if (cmd[i] != ' ')
			{
				count++;
				while (cmd[i] && cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|')
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
	int cmd_len;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			if (cmd[i] == '\'')
			{
				cmd_len = i;
				while (cmd[i] && cmd[i] != '\'')
					i++;
				cmd_len = i - cmd_len;
				tokens[count] = malloc(cmd_len + 1);
				ft_strlcpy(tokens[count], cmd + i - cmd_len, cmd_len + 1);
				count++;
			}
			if ((cmd[i] == '<' && cmd[i] == cmd[i + 1]) || (cmd[i] == '>' && cmd[i] == cmd[i + 1]))
			{
				tokens[count] = malloc(3);
				ft_strlcpy(tokens[count], cmd + i, 3);
				count++;
				i += 2;
			}
			if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
			{
				tokens[count] = malloc(2);
				ft_strlcpy(tokens[count], cmd + i, 2);
				count++;
				i++;
			}
			if (cmd[i] != ' ')
			{
				cmd_len = i;
				while (cmd[i] && cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|')
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
	printf("count: %d\n", count);
	return (tokens);
}

char **tokenize(char *cmd)
{
	int	token_number;
	char	**tokens;

	printf("cmd: %s\n", cmd);
	token_number = count_tokens(cmd);
	tokens = malloc((token_number + 1) * sizeof(char *));
	printf("token_number: %d\n", token_number);
	tokens = fill_tokens(tokens, cmd);
    return (tokens);
}
