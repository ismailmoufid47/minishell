#include "../include/shell.h"

extern char	**environ;

char	*get_cwd(t_envp *envp)
{
	while (envp)
	{
		if (!ft_strcmp(envp->name, "PWD"))
			return (envp->value);
		envp = envp->next;
	}
	return (getcwd(NULL, 0));
}

void	pwd(t_envp *envp)
{
	printf("%s\n", get_cwd(envp));
}

int main()
{
	t_envp *envp;


	envp = set_envp();
	if (!envp)
	{
		ft_putstr_fd("Error initializing environment variables\n", 2);
		return (1);
	}
	pwd(envp);
	return (0);
}
