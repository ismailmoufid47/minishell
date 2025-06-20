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

#include "../include/shell.h"

char	**ft_split_and_add_quotes(char *var, int is_here_doc)
{
	char	**result;
	char	*tmp;
	int		i;

	result = ((i = -1), ft_split(var, ' '));
	if (!result)
		return (NULL);
	while (result[++i])
	{
		if (!is_here_doc)
		{
			if (i > 0)
				result[i] = ((tmp = result[i]), ft_strjoin(" \"", result[i]));
			else
				result[i] = ((tmp = result[i]), ft_strjoin("\"", result[i]));
		}
		else
			result[i] = ((tmp = result[i]), ft_strjoin(result[i], " "));
		free(tmp);
		if (!is_here_doc)
			result[i] = ((tmp = result[i]), ft_strjoin(result[i], "\""));
		if (!is_here_doc)
			free(tmp);
	}
	return (result);
}

char	*join_split_result(char *cmd, char **split, int start, int varln)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	if (!split || !*split)
		return (ft_free_split(split), ft_strjoin(cmd, cmd + start + varln));
	while (split[i])
	{
		if (i == 0)
			result = ft_strjoin(cmd, split[i]);
		else
		{
			result = ((tmp = result), ft_strjoin(result, split[i]));
			free(tmp);
		}
		i++;
	}
	if (i)
	{
		result = ((tmp = result), ft_strjoin(result, cmd + start + varln));
		free(tmp);
	}
	ft_free_split(split);
	return (result);
}
