/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:19:22 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_formattoi(char **format)
{
	int	nbr;

	nbr = 0;
	while (**format >= '0' && **format <= '9')
	{
		nbr = nbr * 10 + (**format - '0');
		(*format)++;
	}
	return (nbr);
}

t_flags	parse_precision(char **format, t_flags flags)
{
	if (**format == '.')
	{
		(*format)++;
		flags.precision = 1;
		flags.zero = 0;
		flags.precision_value = ft_formattoi(format);
	}
	return (flags);
}

t_flags	parse_flags( char **format)
{
	t_flags	flags;

	flags = (t_flags){0};
	while (**format == '+' || **format == ' ' || **format == '-'
		|| **format == '0' || **format == '#')
	{
		if (**format == ' ')
			flags.space = 1;
		if (**format == '+')
			flags.plus = 1;
		if (**format == '-')
			flags.minus = 1;
		if (**format == '0')
			flags.zero = 1;
		if (**format == '#')
			flags.hash = 1;
		(*format)++;
	}
	flags.width = ft_formattoi(format);
	flags = parse_precision(format, flags);
	return (flags);
}

void	check_format(char **format, va_list args, int *written)
{
	t_flags	flags;

	flags = parse_flags(format);
	if (**format == '%')
		*written += ft_putchar('%', flags);
	else if (**format == 'c')
		*written += ft_putchar(va_arg(args, int), flags);
	else if (**format == 's')
		*written += ft_putstr(va_arg(args, char *), flags);
	else if (**format == 'p')
	{
		flags.hash = 1;
		flags.precision = 0;
		*written += ft_putptr(va_arg(args, unsigned long), flags);
	}
	else if (**format == 'd' || **format == 'i')
		*written += ft_putnbr(va_arg(args, int), flags);
	else if (**format == 'u')
		*written += ft_putnbru(va_arg(args, unsigned int), flags);
	else if (**format == 'x')
		*written += ft_puthex(va_arg(args, unsigned int), 0, flags);
	else if (**format == 'X')
		*written += ft_puthex(va_arg(args, unsigned int), 1, flags);
	else
		*written += ft_putchar(**format, flags);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		written;

	written = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			check_format((char **)&format, args, &written);
		}
		else
			written += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (written);
}
