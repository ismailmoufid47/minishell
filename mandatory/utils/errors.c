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

void	export_error(char *identifier)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	command_not_found(char *cmd)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(cmd);
	exit (127);
}
