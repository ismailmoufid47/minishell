/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismail <ismail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:17:45 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/08 02:30:16 by ismail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/shell.h"

void	error(char *error_prefix)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(error_prefix);
	exit(EXIT_FAILURE);
}
