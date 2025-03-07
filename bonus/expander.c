#include "include/shell.h"

char	*search_and_replace(char *cmd, int start)
{
	int variable_len;
	char	variable_name[1024];
	char	*var;
	char	*result;
    int i;

	variable_len = 0;
    i = start;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\n')
	{
		variable_len++;
		i++;
	}
	ft_strlcpy(variable_name, cmd + start, variable_len + 1);
	var = getenv(variable_name);
    cmd[start - 1] = '\0';
	result = ft_strjoin(cmd, var);
	result = ft_strjoin(result, cmd + start + variable_len);
    return (result);
}

char	*expand_env_variable(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '$')
		{
			cmd_line = search_and_replace(cmd_line, i + 1);
			i = 0;
		}
		i++;
	}
    return (cmd_line);
}