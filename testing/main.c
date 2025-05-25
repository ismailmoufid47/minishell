/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:50:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/25 15:45:10 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "../mandatory/include/shell.h"
#include <dirent.h>

typedef enum e_patt_type
{
	FIRST,
	MIDDLE,
	END
}	t_patt_type;
typedef struct s_pattern
{
	t_patt_type type;
	char *value;
	struct s_pattern *next;
}	t_pattern;


int	match_front(char *file, char *front)
{
	int i = 0;
	if (front == NULL)
		return 1;
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
	if (end == NULL)
		return 1;
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

int find_the_star(char *pattern)
{
	int i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
			return i;
		i++;
	}
	return -1;
}

char **match_wild_card(char **files, char *pattern)
{
	int len = strlen(pattern);
	int star = find_the_star(pattern);
	char *front = NULL;
	char *end = NULL;
	pattern[star]  = '\0';
	if (star == 0)
		end = pattern + 1;
	else if (star == len)
		front = pattern;
	else
	{
		front = pattern;
		end = &(pattern[star]) + 1;
	}
	int i = 0;
	while (files[i])
	{
		if (!(match_front(files[i], front) && match_end(files[i], end)))
			files[i][0] = 0;
		i++;
	}
	return files;
}

int	main(int argc, char **argv)
{
	char			*path = ".";
	DIR				*dir = opendir(path);
	struct dirent *entry = 1;
	char			**files = malloc(100 * sizeof(char *));
	char			*pattern = argv[1];
	int i = 0;

	printf("dir fd --> %d\n", dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		if (entry)
			files[i++] = entry->d_name;
	}
	files[i] = NULL;
	printf("all files :\n");
	print_files(files);
	files = match_wild_card(files, pattern);
	printf("after choose\n");
	print_files(files);
	
}
