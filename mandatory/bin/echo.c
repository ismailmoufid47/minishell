#include "../shell.h"

void	check_dash_n_option(char *str, int *option)
{
	if (!ft_strcmp(str, "-n"))
		*option = 1;
	else
		*option = 0;
}

void	print_argument(char **argv, int argc, int option)
{
	int	i;

	i = option + 1;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
		i++;
	}
	if (option == 0)
		printf("\n");
}

int	main(int argc, char **argv)
{
	int	new_line;

	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	check_dash_n_option(argv[1], &new_line);
	print_argument(argv, argc, new_line);
	return (0);
}
