/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:50:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/25 20:47:17 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
// #include "../mandatory/include/shell.h"
#include <dirent.h>

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

// char **match_wild_card(char **files, char *pattern)
// {
// 	int len = strlen(pattern);
// 	int star = find_the_star(pattern);
// 	char *front = NULL;
// 	char *end = NULL;
// 	pattern[star]  = '\0';
// 	if (star == 0)
// 		end = pattern + 1;
// 	else if (star == len)
// 		front = pattern;
// 	else
// 	{
// 		front = pattern;
// 		end = &(pattern[star]) + 1;
// 	}
// 	int i = 0;
// 	while (files[i])
// 	{
// 		if (!(match_front(files[i], front) && match_end(files[i], end)))
// 			files[i][0] = 0;
// 		i++;
// 	}
// 	return files;
// }
// int	match_lit(char *file, char **lits)
// {
// 	if (!*list)
// 		return (1);
// 	if (strstr()) //ft_
// }


// char **match_wild_card(char **files, char *pattern)
// {
// 	char	**lits;
// 	int		i;

// 	lits = ft_split(pattern, '*');
// 	i = 0;
// 	while (files[i])
// 	{
// 		if (!match_lit(files[i], lits))
// 			files[i][0] = '\0';
// 		i++;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	char			*path = ".";
// 	DIR				*dir = opendir(path);
// 	struct dirent *entry = 1;
// 	char			**files = malloc(100 * sizeof(char *));
// 	char			*pattern = argv[1];
// 	int i = 0;

// 	printf("dir fd --> %d\n", dir);
// 	while (entry != NULL)
// 	{
// 		entry = readdir(dir);
// 		if (entry)
// 			files[i++] = entry->d_name;
// 	}
// 	files[i] = NULL;
// 	printf("all files :\n");
// 	print_files(files);
// 	files = match_wild_card(files, pattern);
// 	printf("after choose\n");
// 	print_files(files);
	
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wildcard_match(const char *pattern, const char *file)
{
    const char *last_star;
    const char *last_match;

	last_star = NULL;
	last_match = NULL;
    while (*file)
	{
        if (*pattern == '*')
		{
            while (*pattern == '*')
                pattern++;
            if (!*pattern)
                return 1;
            last_star  = pattern;
            last_match = file;
        }
        else if (*pattern == *file)
		{
            pattern++;
            file++;
        }
        else if (last_star)
		{
            pattern  = last_star;
            file     = ++last_match;
        }
        else
            return 0;
    }
    while (*pattern == '*')
        pattern++;
    return (*pattern == '\0');
}

char **match_wild_card(char **files, const char *pattern)
{
    for (int i = 0; files[i]; i++) {
        if (!wildcard_match(pattern, files[i]))
            files[i][0] = '\0';
    }
    return files;
}

int main(void)
{
    char *files[] = {"abkbc", "foo.txt", "foobar.c", "testfoo", "foo123bar", "barfoo", NULL};
    const char *patterns[] = {"a*bb*c", "foo*", "*bar", "fo*", "*o?3*", "*ba*", NULL};

    for (int p = 0; patterns[p]; p++) {
        int count = 0;
        while (files[count])
            count++;
        char **copy = malloc((count + 1) * sizeof(char *));
        for (int i = 0; i < count; i++)
            copy[i] = strdup(files[i]);
        copy[count] = NULL;

        printf("Pattern: '%s'\n", patterns[p]);
        match_wild_card(copy, patterns[p]);
        for (int i = 0; copy[i]; i++) {
            if (copy[i][0] != '\0')
                printf("  Match: %s\n", copy[i]);
            free(copy[i]);
        }
        free(copy);
        printf("\n");
    }

    return 0;
}
