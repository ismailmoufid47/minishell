/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:34:24 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	write_prefix(unsigned int n, int upper, t_flags flags)
{
	int	written;

	written = 0;
	if (upper && flags.hash && n)
		written += write(1, "0X", 2);
	else if (flags.hash && n)
		written += write(1, "0x", 2);
	return (written);
}

int	write_hex(unsigned int n, int upper)
{
	int	written;

	written = 0;
	if (n >= 16)
		written += write_hex(n / 16, upper);
	if (upper)
		written += write(1, &"0123456789ABCDEF"[n % 16], 1);
	else
		written += write(1, &"0123456789abcdef"[n % 16], 1);
	return (written);
}

int	ft_puthex(unsigned int n, int upper, t_flags flags)
{
	int	len;
	int	written;

	written = 0;
	len = ft_nbrlen(n, 1, flags.hash);
	if (flags.precision && n == 0 && flags.precision_value == 0)
		len = 0;
	if (flags.precision && flags.precision_value > len)
		len = flags.precision_value;
	if (flags.hash && n)
		len += 2;
	if (!flags.minus && !flags.zero)
		written += write_padding(len, flags, ' ');
	written += write_prefix(n, upper, flags);
	if (!flags.minus && flags.zero)
		written += write_padding(len, flags, '0');
	while (flags.precision_value-- > ft_nbrlen(n, 1, 0))
		written += write(1, "0", 1);
	if (!(flags.precision && !n && flags.precision_value < 0))
		written += write_hex(n, upper);
	if (flags.minus)
		written += write_padding(len, flags, ' ');
	return (written);
}
