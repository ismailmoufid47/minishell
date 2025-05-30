#include "../include/shell.h"

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	while (--i > 0)
		printf("%s\n", envp[i]);
}

int	main(int argc, char	**argv, char **envp)
{
	(void)argc;
	(void)argv;
	print_envp(envp);
}
