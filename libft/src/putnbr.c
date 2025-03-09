/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:46:09 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/11 13:23:04 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	write_padding(int len, t_flags flags, char pad_char)
{
	int	written;

	written = 0;
	while (flags.width > len)
	{
		written += write(1, &pad_char, 1);
		flags.width--;
	}
	return (written);
}

int	write_sign_and_prefix(long *n, t_flags flags)
{
	int	written;

	written = 0;
	if (flags.space && !flags.plus && *n >= 0)
		written += write(1, " ", 1);
	if (flags.plus && *n >= 0)
		written += write(1, "+", 1);
	if (*n < 0)
	{
		written += write(1, "-", 1);
		*n = -*n;
	}
	return (written);
}

int	write_number(long n)
{
	int	written;

	written = 0;
	if (n > 9)
		written += write_number(n / 10);
	written += write(1, &(char){(n % 10) + '0'}, 1);
	return (written);
}

int	calculate_length(long n, t_flags flags)
{
	int	len;

	len = ft_nbrlen(n, 0, 0);
	if (flags.precision && flags.precision_value > len - (n < 0))
		len = flags.precision_value + (n < 0);
	if (flags.precision && n == 0 && flags.precision_value == 0)
		len = 0;
	if ((flags.space || flags.plus) && n >= 0)
		len++;
	return (len);
}

int	ft_putnbr(long n, t_flags flags)
{
	int		len;
	int		written;

	written = 0;
	len = calculate_length(n, flags);
	if (!flags.minus && !flags.zero)
		written += write_padding(len, flags, ' ');
	written += write_sign_and_prefix(&n, flags);
	if (!flags.minus && flags.zero)
		written += write_padding(len, flags, '0');
	flags.precision_value += !n;
	while (flags.precision_value-- > ft_nbrlen(n, 0, 0))
		written += write(1, "0", 1);
	if (!(flags.precision && !n && !flags.precision_value))
		written += write_number(n);
	if (flags.minus)
		written += write_padding(len, flags, ' ');
	return (written);
}
