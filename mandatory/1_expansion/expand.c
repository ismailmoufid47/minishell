#include "../include/shell.h"

// can't start with a digit expample: $12var expands to 2var
// can only contain alphanumeric characters and underscores
char	*search_and_replace(char *cmd, int start)
{
	char	variable_name[1024];
	char	*result;
	char	*var;
	int		i;
	int		variable_len;

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
	if (!var && ft_isdigit(cmd[start]))
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
	return (cmd_line);
}
