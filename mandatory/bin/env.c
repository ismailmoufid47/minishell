#include "../include/shell.h"

void	print_envp(char **envp)
{
	if (*envp)
	{
		print_envp(&(*++envp));
		printf("%s\n", *envp);
	}
}

int	main(int argc, char	**argv, char **envp)
{
	(void)argc;
	(void)argv;
	print_envp(envp);
}
