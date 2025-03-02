/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:17:45 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/01 18:35:04 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	error(char *error_prefix)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(error_prefix);
	exit(EXIT_FAILURE);
}
