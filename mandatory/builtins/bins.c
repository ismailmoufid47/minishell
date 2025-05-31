#include "../include/shell.h"

void	print_argument(char **argv)
{
	int	i;

	i = 1;
	if (!ft_strcmp(argv[1], "-n"))
		i = 2;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (strcmp(argv[1], "-n"))
		printf("\n");
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	while (--i > 0)
		printf("%s\n", envp[i]);
	ft_free_split(envp);
}

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
