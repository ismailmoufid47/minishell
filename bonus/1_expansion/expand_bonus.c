/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   expand_bonus.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

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
char	*search_and_replace(char *cmd, int start, t_envp *envp)
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
	split_result = ft_split_and_add_quotes(var);
	return (join_split_result(cmd, split_result, start, variable_name_len));
}

void	check_delimiter_quotes(char **cmd, char *dlmtr, int dl_start, int redir)
{
	int		i;
	int		quote_flag;
	char	*tmp;
	char	*tmp2;

	i = 0;
	quote_flag = 0;
	while (dlmtr[i] && !is_single_operator(dlmtr[i])
		&& dlmtr[i] != ' ')
	{
		if (dlmtr[i] == '\'' || dlmtr[i] == '"')
			quote_flag = 1;
		i++;
	}
	i = 0;
	if (quote_flag && redir == 2)
	{
		tmp = ft_substr(*cmd, 0, dl_start);
		tmp2 = ft_strjoin(tmp, "\"\"");
		free(tmp);
		tmp = ft_strjoin(tmp2, dlmtr);
		free(tmp2);
		free(*cmd);
		*cmd = tmp;
	}
}

struct s_data
{
	int		i;
	int		sq_flag;
	int		dq_flag;
	int		redir_is_prev;
	char	*tmp;
};

void	check_redirection(struct s_data *data, char **line)
{
	if (data->redir_is_prev)
	{
		while ((*line)[data->i] && (*line)[data->i] == ' ')
			(data->i)++;
		check_delimiter_quotes(line, (*line) + data->i,
			data->i, data->redir_is_prev);
		while ((*line)[data->i] && !is_single_operator((*line)[data->i])
			&& (*line)[data->i] != ' ')
			(data->i)++;
		data->redir_is_prev = 0;
	}
	if (is_special_token(*line + data->i)
		&& !data->dq_flag && !data->sq_flag)
	{
		data->redir_is_prev = 1;
		if (!ft_strncmp(*line + data->i, "<<", 2))
			data->redir_is_prev = 2;
		(data->i)++;
	}
	if ((*line)[data->i] == '\'' && !data->dq_flag)
		data->sq_flag = !data->sq_flag;
	else if ((*line)[data->i] == '"' && !data->sq_flag)
		data->dq_flag = !data->dq_flag;
}

char	*expand_env_variable(char *cmd_line, t_envp *envp)
{
	struct s_data	data;

	data.redir_is_prev = ((data.i = 0), (data.sq_flag = 0), 0);
	data.dq_flag = 0;
	while (cmd_line && cmd_line[data.i])
	{
		check_redirection(&data, &cmd_line);
		if ((cmd_line[data.i] == '$' && !data.sq_flag && !data.redir_is_prev)
			&& (
				(cmd_line[data.i + 1]
					&& (ft_strchr("_'?", cmd_line[data.i + 1])))
				|| ft_isalnum(cmd_line[data.i + 1])
				|| (cmd_line[data.i + 1] == '"' && !data.dq_flag)))
		{
			data.tmp = cmd_line;
			cmd_line
				= search_and_replace(cmd_line, data.i + 1, envp);
			free(data.tmp);
			if (data.i && cmd_line[data.i] == '"')
				data.i--;
		}
		if (cmd_line && cmd_line[data.i])
			data.i++;
	}
	return (cmd_line);
}
