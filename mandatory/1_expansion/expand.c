#include "../include/shell.h"

// can't start with a digit expample: $12var expands to 2var
// can only contain alphanumeric characters and underscores
char	*search_and_replace(char *cmd, int start, t_envp *envp)
{
	char	variable_name[1024];
	char	*result;
	char	*var;
	int		i;
	int		variable_len;

	variable_len = ft_isdigit(cmd[start]);
	i = start;
	while (cmd[i]
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '?')
		&& !ft_isdigit(cmd[start]))
	{
		variable_len++;
		i++;
	}
	ft_strlcpy(variable_name, cmd + start, variable_len + 1);
	var = ft_get_env_val(envp, variable_name);
	if (variable_len == 0)
		var = "$";
	if (!var || ft_isdigit(cmd[start]))
		var = "";
	cmd[start - 1] = '\0';
	var = ft_strjoin(cmd, var);
	result = ft_strjoin(var, cmd + start + variable_len);
	return (free(var), result);
}

char	*expand_env_variable(char *cmd_line, t_envp *envp)
{
	int	i;
	int	expanded;

	i = 0;
	expanded = 0;
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
			expanded = 1;
			if (cmd_line[i + 1])
				cmd_line = search_and_replace(cmd_line, i + 1, envp);
		}
		if (cmd_line[i])
			i++;
	}
	if (!expanded)
		cmd_line = ft_strdup(cmd_line);
	return (cmd_line);
}
