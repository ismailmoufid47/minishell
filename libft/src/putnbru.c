/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbru.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:54:34 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/11 13:23:18 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	write_number_u(unsigned int n)
{
	int	written;

	written = 0;
	if (n > 9)
		written += write_number_u(n / 10);
	written += write(1, &(char){(n % 10) + '0'}, 1);
	return (written);
}

int	calculate_length_u(unsigned int n, t_flags flags)
{
	int	len;

	len = ft_nbrlen(n, 0, 0);
	if (flags.precision && flags.precision_value > len)
		len = flags.precision_value;
	if (flags.precision && n == 0 && flags.precision_value == 0)
		len = 0;
	if (flags.space || flags.plus)
		len++;
	return (len);
}

int	ft_putnbru(unsigned int n, t_flags flags)
{
	int		len;
	int		written;

	written = 0;
	len = calculate_length_u(n, flags);
	if (!flags.minus && !flags.zero)
		written += write_padding(len, flags, ' ');
	if (flags.space && !flags.plus)
		written += write(1, " ", 1);
	if (flags.plus)
		written += write(1, "+", 1);
	if (!flags.minus && flags.zero)
		written += write_padding(len, flags, '0');
	flags.precision_value += !n;
	while (flags.precision_value-- > ft_nbrlen(n, 0, 0))
		written += write(1, "0", 1);
	if (!(flags.precision && !n && !flags.precision_value))
		written += write_number_u(n);
	if (flags.minus)
		written += write_padding(len, flags, ' ');
	return (written);
}
