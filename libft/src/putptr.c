/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:32:37 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_nbrlen(long nbr, int hex, int hash)
{
	int				len;
	int				base;
	unsigned long	n;

	len = 0;
	base = 10;
	n = nbr;
	if (nbr < 0 && !hex)
		n = -nbr;
	if (hex)
		base = 16;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	if (hash && hex && nbr)
		len += 0;
	if (!nbr)
		return (len + 1);
	if (nbr < 0 && !hex)
		len++;
	return (len);
}

int	ft_putptr(unsigned long n, t_flags flags)
{
	int		len;
	char	padding_char;
	int		written;

	written = 0;
	padding_char = ' ';
	len = ft_nbrlen(n, 1, 1) + (!n * 2) + (n > 0) * 2 ;
	if (!flags.minus && flags.width > len)
		while (flags.width-- > len)
			written += write(1, &padding_char, 1);
	if (flags.hash)
		written += write(1, "0x", 2);
	if (n >= 16)
		written += ft_putptr(n / 16, (t_flags){0});
	written += write(1, &"0123456789abcdef"[n % 16], 1);
	if (flags.minus && flags.width > len)
		while (flags.width-- > len)
			written += write(1, &padding_char, 1);
	return (written);
}
