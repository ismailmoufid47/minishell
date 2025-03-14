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

t_envp	*get_env_node(t_envp *envp, char *var_name)
{
	while (envp)
	{
		if (!ft_strcmp(var_name, envp->name))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
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
