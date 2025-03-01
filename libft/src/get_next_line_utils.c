/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:27:13 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/12 21:20:44 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen2(const char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin2(char *line, char *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	string = malloc(ft_strlen2(line) + ft_strlen2(s2) + 1);
	if (!string)
		return (free(line), NULL);
	i = 0;
	if (line)
	{
		while (line[i])
		{
			string[i] = line[i];
			i++;
		}
		free(line);
	}
	j = 0;
	while (s2[j])
	{
		string[i + j] = s2[j];
		j++;
	}
	string[i + j] = '\0';
	return (string);
}

char	*ft_strdup2(char *line)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(ft_strlen2(line) + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i++])
		new_line[i - 1] = line[i - 1];
	new_line[i - 1] = '\0';
	return (new_line);
}

int	ft_strchr2(const char *line, int c)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i++])
		if (line[i - 1] == c)
			return (i - 1);
	return (-1);
}

char	*ft_substr2(char *line, unsigned int start, size_t len)
{
	size_t	line_len;
	size_t	final;
	char	*sub;
	size_t	i;

	if (!line)
		return (NULL);
	line_len = ft_strlen2(line);
	if (start >= line_len)
		return (malloc(1));
	final = line_len - start;
	if (final > len)
		final = len;
	sub = malloc(final + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i++ < final && line[start + i - 1]) 
		sub[i - 1] = line[start + i - 1];
	sub[i - 1] = '\0';
	return (sub);
}
