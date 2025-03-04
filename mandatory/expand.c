#include "shell.h"

// can't start with a digit expample: $12var expands to 2var
// can only contain alphanumeric characters and underscores
char	*search_and_replace(char *cmd, int start)
{
	int		variable_len;
	char	variable_name[1024];
	char	*var;
	char	*result;
	int		i;

	variable_len = ft_isdigit(cmd[start]);
	i = start;
	while (cmd[i]
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_') && !ft_isdigit(cmd[start]))
	{
		variable_len++;
		i++;
	}
	ft_strlcpy(variable_name, cmd + start, variable_len + 1);
	var = getenv(variable_name);
	if (!var)
		var = "";
	if (variable_len == 0)
		var = "$";
	cmd[start - 1] = '\0';
	var = ft_strjoin(cmd, var);
	result = ft_strjoin(var, cmd + start + variable_len);
	return (free(var), result);
}

char	*expand_env_variable(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'')
		{
			i++;
			while (cmd_line[i] && cmd_line[i] != '\'')
				i++;
		}
		if (cmd_line[i] == '$')
		{
			cmd_line = search_and_replace(cmd_line, i + 1);
			i = 0;
		}
		if (cmd_line[i])
			i++;
	}
	printf("\nCmdline after expansion: %s\n\n", cmd_line);
	return (cmd_line);
}
