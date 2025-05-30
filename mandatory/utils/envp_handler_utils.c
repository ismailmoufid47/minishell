#include "../include/shell.h"

t_envp	*replace_missing_envp(t_envp *envp)
{
	t_envp	*node;
	char	*str;

	if (ft_get_env_val(envp, "PWD") == NULL)
	{
		str = ft_strjoin("PWD=", getcwd(NULL, 0));
		*(ft_strchr(str, '=')) = 0;
		node = create_envp_node(str);
		free(str);
		node->value = ft_strdup(getcwd(NULL, 0));
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
