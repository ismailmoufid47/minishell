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
	char	*tmp;

	variable_len = ft_isdigit(cmd[start]);
	i = start - 1;
	while (cmd[++i]
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '?')
		&& !ft_isdigit(cmd[start]))
		variable_len++;
	ft_strlcpy(variable_name, cmd + start, variable_len + 1);
	var = ft_strjoin(ft_get_env_val(envp, variable_name), "\"");
	if (variable_len == 0)
	// {
	// 	free(var);
		var = strdup("$");
	// }
	tmp = cmd;
	cmd[start - 1] = '\0';
	if (!var || ft_isdigit(cmd[start]) || cmd[start] == '\"' || cmd[start] == '\'')
		var = strdup("");
	else
		cmd = ft_strjoin(cmd, "\"");
	var = ft_strjoin(cmd, var);
	result = ft_strjoin(var, tmp + start + variable_len);
	return (result);
}

char	*expand_env_variable(char *cmd_line, t_envp *envp)
{
	int		i;
	int		expanded;
	int		dq_flag;
	int		sq_flag;
	int		here_doc_is_prev;

	i = 0;
	expanded = 0;
	dq_flag = 0;
	sq_flag = 0;
	here_doc_is_prev = 0;
	while (cmd_line[i])
	{
		if (here_doc_is_prev)
		{
			while (cmd_line[i] && cmd_line[i] == ' ')
				i++;
			while (cmd_line[i] && !is_special_operator(cmd_line[i])
				&& cmd_line[i] != ' ')
				i++;
			here_doc_is_prev = 0;
		}
		if (cmd_line[i] == '<'  && cmd_line[i + 1] == '<' 
			&& !dq_flag && !sq_flag)
		{
			here_doc_is_prev = 1;
			i += 2;
			continue ;
		}
		if (cmd_line[i] == '\'' && !dq_flag)
			sq_flag = !sq_flag;
		else if (cmd_line[i] == '"' && !sq_flag)
			dq_flag = !dq_flag;
		if (cmd_line[i] == '$' && !sq_flag && !here_doc_is_prev)
		{
			expanded = 1;
			if (cmd_line[i + 1] && (strchr("_?", cmd_line[i + 1]) || ft_isalpha(cmd_line[i + 1])))
				cmd_line = search_and_replace(cmd_line, i + 1, envp);
		}
		if (cmd_line[i])
			i++;
	}
	if (!expanded)
		cmd_line = ft_strdup(cmd_line);
	return (cmd_line);
}
