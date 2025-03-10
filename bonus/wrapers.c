/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:08:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/09 20:42:08 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

int	open_wraper(char *file, int open_mode, int create_permissions)
{
	int	fd;

	if (!create_permissions)
		fd = open(file, open_mode);
	else
		fd = open(file, open_mode, create_permissions);
	if (fd == -1)
		error(ft_strdup("open"));
	return (fd);
}
