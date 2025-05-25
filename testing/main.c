/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:50:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/25 13:42:43 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "../mandatory/include/shell.h"
#include <dirent.h>

int	match_front(char *file, char *front)
{
	int i = 0;
	while (file[i] && front[i])
	{
		if (file[i] != front[i])
			break ;
		i++;
	}
	if (front[i] == 0)
		return 1;
	return 0;
}

char *rev_str(char *str)
{
	char *rev = strdup(str);
	int start = 0;
	int len = strlen(str) - 1;
	char tmp;
	while (start < len)
	{
		tmp = rev[start];
		rev[start] = rev[len];
		rev[len] = tmp;
		start++;
		len--;
	}
	return rev;
}

int match_end(char *file , char *end)
{
	file = rev_str(file);
	end = rev_str(end);
	return (match_front(file, end));
}

void	print_files(char **files)
{
	int i = 0;
	while (files[i])
		printf("--> %s\n", files[i++]);
}

int	main()
{
	char			*path = ".";
	DIR				*dir = opendir(path);
	struct dirent *entry = 1;
	char			*files[100];
	int i = 0;

	printf("dir fd --> %d\n", dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		if (entry)
			files[i++] = entry->d_name;
	}
	files[i] = NULL;
	print_files(files);
}
