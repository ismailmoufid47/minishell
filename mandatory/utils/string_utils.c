/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   string_utils.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	skip_spaces(const char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

void	fill_substring(char **table, char **str)
{
	int		count;
	int		i;

	count = 0;
	while ((*str)[count] == ' ')
		count++;
	while ((*str)[count] != ' ' && (*str)[count])
		count++;
	i = 0;
	*table = malloc((count + 1) * sizeof(char));
	while (i < count)
	{
		(*table)[i] = (**str);
		(*str)++;
		i++;
	}
	(*table)[i] = '\0';
}

char	**ft_split_merciful(char *str)
{
	char	**re;
	int		i;
	int		count;

	i = 0;
	count = count_substring(str, ' ');
	re = malloc((count + 1) * sizeof(char *));
	if (!re)
		return (NULL);
	while (i < count - 1)
	{
		fill_substring(&(re[i]), &str);
		i++;
	}
	re[i] = malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_strlcpy(re[i++], str, ft_strlen(str) + 1);
	re[i] = NULL;
	return (re);
}

char	**char_to_double_char(char *str)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(str);
	result[1] = NULL;
	return (result);
}
