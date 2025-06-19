#include "../include/shell_bonus.h"

int	extract_variable_value(t_envp *envp, char *cmd, char **var, int start)
{
	char	variable_name[1024];
	int		variable_name_len;
	int		i;

	variable_name_len = ft_isdigit(cmd[start]);
	i = start - 1;
	while (cmd[++i]
		&& (ft_isalnum(cmd[i]) || cmd[i] == '_' )
		&& !ft_isdigit(cmd[start]))
		variable_name_len++;
	if (!variable_name_len && cmd[i] == '?')
		variable_name_len = 1;
	ft_strlcpy(variable_name, cmd + start, variable_name_len + 1);
	*var = ft_get_env_val(envp, variable_name);
	if (variable_name_len == 0 && (cmd[i] == '\'' || cmd[i] == '"'))
		cmd[i - 1] = ' ';
	return (variable_name_len);
}

// can't start with a digit expample: $12var expands to 2var
// can only contain alphanumeric characters and underscores
char	*search_and_replace(char *cmd, int start, t_envp *envp, int is_here_doc)
{
	char	*var;
	char	*result;
	char	**split_result;
	int		variable_name_len;

	result = NULL;
	variable_name_len = extract_variable_value(envp, cmd, &var, start);
	if (variable_name_len == 0)
		return (ft_strdup(cmd));
	cmd[start - 1] = '\0';
	if (!var || !*var || ft_isdigit(cmd[start]) || cmd[start] == '\"'
		|| cmd[start] == '\'')
	{
		var = ft_strdup("");
		result = ft_strjoin(cmd, var);
		free(var);
		var = result;
		result = ft_strjoin(result, cmd + start + variable_name_len);
		free(var);
		return (result);
	}
	split_result = ft_split_and_add_quotes(var, is_here_doc);
	return (join_split_result(cmd, split_result, start, variable_name_len));
}

void	check_delimiter_quotes(char **cmd_line, char *delimiter, int del_start)
{
	int		i;
	int		quote_flag;
	char	*tmp;
	char	*tmp2;

	i = 0;
	quote_flag = 0;
	while (delimiter[i] && !is_single_operator(delimiter[i])
		&& delimiter[i] != ' ')
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			quote_flag = 1;
		i++;
	}
	i = 0;
	if (quote_flag)
	{
		tmp = ft_substr(*cmd_line, 0, del_start);
		tmp2 = ft_strjoin(tmp, "''");
		free(tmp);
		tmp = ft_strjoin(tmp2, delimiter);
		free(tmp2);
		free(*cmd_line);
		*cmd_line = tmp;
	}
}

void	handle_hdoc_del(char **line, int *sq_flag, int *i, int *hdoc_is_prev)
{
	static int		dq_flag;

	if (*hdoc_is_prev)
	{
		while ((*line)[*i] && (*line)[*i] == ' ')
			(*i)++;
		check_delimiter_quotes(line, (*line) + *i, *i);
		while ((*line)[*i] && !is_single_operator((*line)[*i])
			&& (*line)[*i] != ' ')
			(*i)++;
		*hdoc_is_prev = 0;
	}
	if ((*line)[*i] == '<' && (*line)[*i + 1] == '<'
		&& !dq_flag && !*sq_flag)
	{
		*hdoc_is_prev = 1;
		(*i)++;
	}
	if ((*line)[*i] == '\'' && !dq_flag)
		*sq_flag = !*sq_flag;
	else if ((*line)[*i] == '"' && !*sq_flag)
		dq_flag = !dq_flag;
}

char	*expand_env_variable(char *cmd_line, t_envp *envp, int is_here_doc)
{
	int		i;
	int		sq_flag;
	int		here_doc_is_prev;
	char	*tmp;

	here_doc_is_prev = ((i = 0), (sq_flag = 0), 0);
	while (cmd_line && cmd_line[i])
	{
		handle_hdoc_del(&cmd_line, &sq_flag, &i, &here_doc_is_prev);
		if (cmd_line[i] == '$' && !sq_flag && !here_doc_is_prev)
		{
			if (cmd_line[i + 1] && (ft_strchr("_?", cmd_line[i + 1]) //7ydna single wdouble mn strchr
					|| ft_isalpha(cmd_line[i + 1])))
			{
				tmp = cmd_line;
				cmd_line
					= search_and_replace(cmd_line, i + 1, envp, is_here_doc);
				free(tmp);
			}
		}
		if (cmd_line && cmd_line[i])
			i++;
	}
	return (cmd_line);
}
