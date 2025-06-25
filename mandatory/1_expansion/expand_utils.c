/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   expand_utils.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*add_quotes(char *str, int location)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, location);
	tmp2 = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = ft_substr(str, location, ft_strlen(str));
	free(str);
	str = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (str);
}

char	**ft_split_and_add_quotes(char *var)
{
	char	**result;
	char	*tmp;
	int		i;

	result = ((i = -1), ft_split_merciful(var));
	if (!result)
		return (NULL);
	while (result[++i + 1])
	{
		result[i] = add_quotes(result[i], skip_spaces(result[i], 0));
		tmp = ft_strjoin(result[i], "\"");
		free(result[i]);
		result[i] = tmp;
	}
	result[i] = add_quotes(result[i], skip_spaces(result[i], 0));
	result[i] = add_quotes(result[i],
			ft_strchr(&result[i][skip_spaces(result[i], 0)], ' ') - result[i]);
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
