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

	prev = NULL;
	envp = head;
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
			free(envp);
			return (head);
		}
		prev = envp;
		envp = envp->next;
	}
	return (head);
}

t_envp	*create_envp_node(char *var)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->name = ft_strdup(var);
	node->value = ft_strdup((var) + ft_strlen(var) + 1);
	return (node);
}

t_envp	*set_envp(void)
{
	int		i;
	t_envp	*head;
	t_envp	*node;

	i = 0;
	head = NULL;
	while (environ[i])
	{
		*(ft_strchr(environ[i], '=')) = 0;
		node = create_envp_node(environ[i]);
		node->next = head;
		head = node;
		i++;
	}
	node = create_envp_node("?\0000");
	node->next = head;
	head = node;
	return (head);
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
	{
		count++;
		current = current->next;
	}
	result = malloc((count + 1) * sizeof(char *));
	count = 0;
	while (envp)
	{
		tmp = ft_strjoin(envp->name, "=");
		result[count] = ft_strjoin(tmp, envp->value);
		free(tmp);
		count++;
		envp = envp->next;
	}
	result[count] = NULL;
	return (result);
}
