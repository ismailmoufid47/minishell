#include "../include/shell.h"

// can't start with a digit expample: $12var expands to 2var
// can only contain alphanumeric characters and underscores

char **ft_split_and_add_quotes(char *var, int is_here_doc)
{
	char	**result;
	char	*tmp;
	int		i;

	result = ft_split(var, ' ');
	i = 0;
	while (result[i])
	{
		tmp = result[i];
		if (!is_here_doc)
		{
			if (i > 0)
				result[i] = ft_strjoin(" \"", result[i]);
			else
				result[i] = ft_strjoin("\"", result[i]);
		}
		else
			result[i] = ft_strjoin(result[i], " ");
		free(tmp);	
		tmp = result[i];
		if (!is_here_doc)
		{
			result[i] = ft_strjoin(result[i], "\"");
			free(tmp);
		}
		i++;
	}
	return (result);

}

char	*search_and_replace(char *cmd, int start, t_envp *envp, int is_here_doc)
{
	char	variable_name[1024];
	char	*result;
	char	*var;
	int		i;
	int		variable_name_len;
	char	*tmp;
	char	**split_result;

	variable_name_len = ft_isdigit(cmd[start]);
	i = start - 1;
	result = NULL;
	while (cmd[++i]
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_' )
		&& !ft_isdigit(cmd[start]))
		variable_name_len++;
	if (cmd[i] == '?')
		variable_name_len = 1;
	ft_strlcpy(variable_name, cmd + start, variable_name_len + 1);
	var = ft_get_env_val(envp, variable_name);
	if (variable_name_len == 0)
		return (ft_strdup(cmd));
	cmd[start - 1] = '\0';
	if (!var || !*var || ft_isdigit(cmd[start]) || cmd[start] == '\"' || cmd[start] == '\'')
	{
		var = strdup("");
		result = ft_strjoin(cmd, var);
		free(var);
		var = result;
		result = ft_strjoin(result, cmd + start + variable_name_len);
		free(var);
		return (result);
	}
	split_result = ft_split_and_add_quotes(var, is_here_doc);
	i = 0;
	while (split_result && split_result[i])
	{
		tmp = split_result[i];
		if (i == 0)
			result = ft_strjoin(cmd, tmp);
		else
		{
			var = result;
			result = ft_strjoin(result, tmp);
			free(var);
		}
		free(tmp);
		i++;
	}
	if (i)
	{
		var = result;
		result = ft_strjoin(result, cmd + start + variable_name_len);
		free(var);
	}
	free(split_result);
	return (result);
}

char	*expand_env_variable(char *cmd_line, t_envp *envp, int is_here_doc)
{
	int		i;
	int		dq_flag;
	int		sq_flag;
	int		here_doc_is_prev;
	char	*tmp;

	i = 0;
	dq_flag = 0;
	sq_flag = 0;
	here_doc_is_prev = 0;
	while (cmd_line && cmd_line[i])
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
			if (cmd_line[i + 1] && (strchr("_?", cmd_line[i + 1]) || ft_isalpha(cmd_line[i + 1])))
			{
				tmp = cmd_line;
				cmd_line = search_and_replace(cmd_line, i + 1, envp, is_here_doc);
				free(tmp);
			}
		}
		if (cmd_line && cmd_line[i])
			i++;
	}
	return (cmd_line);
}
