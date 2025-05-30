#include "../include/shell.h"

void	error(char *error_prefix)
{
	ft_putstr_fd("Minishell: ", 2);
	perror(error_prefix);
	free(error_prefix);
	exit(EXIT_FAILURE);
}

void	error_fork(t_envp **envp, char *error_prefix)
{

	// (void )(envp);

	ft_putstr_fd("Minishell: ", 2);
	perror(error_prefix);
	free(error_prefix);
	free((*envp)->value);
	(*envp)->value = ft_strdup("1");
}

int	syntax_error(char **tokens, char *error_prefix, t_envp *envp)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_prefix, 2);
	ft_putendl_fd("'", 2);
	ft_free_split(tokens);
	free(envp->value);
	envp->value = ft_strdup("258");
	return (0);
}

void	identifier_error(char *cmd, char *identifier, t_envp *envp)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	free(envp->value);
	envp->value = ft_strdup("1");
}

void	exec_error(t_list **cmd)
{
	struct stat	buf;
	stat((*cmd)->args[0], &buf);
	if (ft_strcmp((*cmd)->args[0], "." ) && ft_strcmp((*cmd)->args[0], "..") && S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd((*cmd)->args[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		free_list(*cmd);
		exit (126);
	}
	if (ft_strchr((*cmd)->args[0], '/') && access((*cmd)->args[0], F_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd((*cmd)->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_list(*cmd);
		exit (127);
	}
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd((*cmd)->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_list(*cmd);
	exit (127);
}