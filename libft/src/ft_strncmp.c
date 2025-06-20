/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-mou <isel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:26:15 by isel-mou          #+#    #+#             */
/*   Updated: 2025/01/08 17:27:51 by isel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
// unsigned bcs char could be more than 127 (max of signed char) 
// and the - of s1 and s2 signed chars isn't the same as 
// the - of their unsigned cast
int	ft_strncmp(const char *s1, const char *s2, size_t max)
{
	while (max && (*s1 || *s2))
	{
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		s1++;
		s2++;
		max--;
	}
	return (0);
}

// int main() {
// 	printf("mine: %d\n",  ft_strncmp("abc\1", "abc\200", 4));
// 	printf("original: %d\n", strncmp("abc\1", "abc\200", 4));
// 	return 0;
// }