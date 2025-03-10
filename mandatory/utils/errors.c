#include "../include/shell.h"

void	error(char *error_prefix)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(error_prefix);
	free(error_prefix);
	exit(EXIT_FAILURE);
}

int	syntax_error(char **tokens, char *error_prefix)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_prefix, 2);
	ft_putendl_fd("'", 2);
	ft_free_split(tokens);
	return (0);
}
