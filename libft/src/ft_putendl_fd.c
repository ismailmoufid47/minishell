/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:40:05 by isel-mou          #+#    #+#             */
/*   Updated: 2025/06/02 16:54:59 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	if (!str)
		ft_putstr_fd("{null}", fd);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}
