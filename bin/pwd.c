#include "../include/shell.h"

char	*get_cwd(t_envp *envp)
{
	while (envp)
	{
		if (!ft_strcmp(envp->name, "PWD"))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

void	pwd(t_envp *envp)
{
	printf("%s\n", get_cwd(envp));
}
