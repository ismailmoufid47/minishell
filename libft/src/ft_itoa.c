/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:16:35 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_count_digits(int n)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

// (if (n < 0)) x 2 for norminette
char	*ft_itoa(int n)
{
	size_t	result_len;
	char	*result;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!n)
		return (ft_strdup("0"));
	result_len = ft_count_digits(n);
	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	if (n < 0)
		result[0] = '-';
	if (n < 0)
		n = -n;
	i = result_len - 1;
	while (n)
	{
		result[i] = ((n % 10) + '0');
		n /= 10;
		i--;
	}
	result[result_len] = '\0';
	return (result);
}
