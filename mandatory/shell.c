/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:07:34 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/03/01 19:01:53 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast *parse(char *cmd_line)
{
	
}

int main()
{
	char	*input;

	while (1)
	{
		input = readline(get_prompt());
		if (input == NULL)
			exit(0);
		print_tree(parse(input));
	}
	return (0);
}
