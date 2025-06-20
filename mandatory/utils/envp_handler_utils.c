/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   envp_handler_utils.c                                :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

t_envp	*replace_missing_envp(t_envp *envp)
{
	t_envp	*node;
	char	*str;
	char	*tmp;

	if (ft_get_env_val(envp, "PWD") == NULL)
	{
		tmp = getcwd(NULL, 0);
		str = ft_strjoin("PWD=", tmp);
		free(tmp);
		*(ft_strchr(str, '=')) = 0;
		node = create_envp_node(str);
		free(str);
		node->next = envp;
		envp = node;
	}
	if (ft_get_env_val(envp, "PATH") == NULL)
	{
		str = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		*(ft_strchr(str, '=')) = 0;
		node = create_envp_node(str);
		free(str);
		node->next = envp;
		envp = node;
	}
	return (envp);
}
