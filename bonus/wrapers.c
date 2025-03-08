/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismail <ismail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:08:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/08 02:30:16 by ismail           ###   ########.fr       */
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
		error("open");
	return (fd);
}
