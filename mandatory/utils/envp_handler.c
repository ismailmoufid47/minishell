/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   envp_handler.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: Jbelkerf && isel-mou <minishell>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/20 13:02:27 by Jbelkerf && isel-mou #+#    #+#          */
/*   Updated: 2025/06/20 13:06:51 by Jbelkerf && isel-mou ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char	*ft_get_env_val(t_envp *envp, char *var_name)
{
	while (envp)
	{
		if (!ft_strcmp(var_name, envp->name))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

t_envp	*remove_envp_var(t_envp *head, char *var_name)
{
	t_envp	*prev;
	t_envp	*envp;
	t_envp	*removable;

	envp = ((prev = NULL), head);
	while (envp)
	{
		if (!ft_strcmp(envp->name, var_name))
		{
			if (!prev)
			{
				removable = envp;
				head = head->next;
				free(removable);
				return (head);
			}
			prev->next = envp->next;
			free(envp->name);
			free(envp->value);
			free(envp);
			return (head);
		}
		envp = ((prev = envp), envp->next);
	}
	return (head);
}

t_envp	*create_envp_node(char *var)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->name = ft_strdup(var);
	node->value = ft_strdup(var + ft_strlen(var) + 1);
	node->next = NULL;
	return (node);
}

t_envp	*set_envp(void)
{
	int		i;
	char	*str;
	t_envp	*envp;
	t_envp	*node;

	i = 0;
	envp = NULL;
	while (environ[i])
	{
		str = ft_strdup(environ[i]);
		*(ft_strchr(str, '=')) = 0;
		node = create_envp_node(str);
		free(str);
		node->next = envp;
		envp = node;
		i++;
	}
	envp = replace_missing_envp(envp);
	node = create_envp_node("?\0000");
	node->next = envp;
	envp = node;
	return (envp);
}

char	**envp_to_char(t_envp *envp)
{
	int		count;
	t_envp	*current;
	char	**result;
	char	*tmp;

	count = 0;
	current = envp;
	while (current)
		current = ((count++), current->next);
	result = malloc((count + 1) * sizeof(char *));
	count = 0;
	while (envp)
	{
		if (!envp->value)
		{
			envp = envp->next;
			continue ;
		}
		tmp = ft_strjoin(envp->name, "=");
		result[count] = ft_strjoin(tmp, envp->value);
		envp = ((free(tmp)), (count++), envp->next);
	}
	result[count] = NULL;
	return (result);
}
