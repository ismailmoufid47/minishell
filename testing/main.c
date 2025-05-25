/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 12:50:37 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/05/25 13:18:42 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "../mandatory/include/shell.h"
#include <dirent.h>


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
		if ( entry && printf("---> %s\n", entry->d_name))
		;
	}
}
