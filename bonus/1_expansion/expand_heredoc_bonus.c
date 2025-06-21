/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   expand_here_doc_bonus.c                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell_bonus.h"

// can't start with a digit expample: $12var expands to 2var
// can only contain alphanumeric characters and underscores
char	*search_and_replace_in_heredoc(char *cmd, int start, t_envp *envp)
{
	char	*var;
	char	*result;
	int		varname_len;

	result = NULL;
	varname_len = extract_variable_value(envp, cmd, &var, start);
	if (varname_len == 0)
		return (ft_strdup(cmd));
	cmd[start - 1] = '\0';
	printf("cmd: %s\n", cmd);
	if (!var || !*var || ft_isdigit(cmd[start]) || cmd[start] == '\"'
		|| cmd[start] == '\'')
	{
		var = ft_strdup("");
		result = ft_strjoin(cmd, var);
		free(var);
		var = result;
		result = ft_strjoin(result, cmd + start + varname_len);
		free(var);
		return (result);
	}
	result = ft_strjoin(cmd, var);
	free(var);
	result = ((var = result), ft_strjoin(result, cmd + start + varname_len));
	return (free(var), result);
}

char	*expand_env_variable_in_heredoc(char *line, t_envp *envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && !ft_strchr("\"' ", line[i + 1]))
		{
			tmp = line;
			line = search_and_replace_in_heredoc(line, i + 1, envp);
			free(tmp);
		}
		if (line && line[i])
			i++;
	}
	return (line);
}
