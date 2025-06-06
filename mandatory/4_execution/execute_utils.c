#include "../include/shell.h"

void	builtin_here_doc(char *delimiter, t_envp *envp)
{
	int		fd1;
	int		fd2;
	char	*input;
	char	*tmp;

	fd1 = open_wrapper("read_line", O_W | O_C | O_T, 0600);
	fd2 = ((input = "NULL"), open_wrapper("read_line", O_RDONLY, 0));
	unlink("read_line");
	tmp = readline("> ");
	while (tmp && ft_strcmp(tmp, delimiter))
	{
		input = expand_env_variable(tmp, envp, 0);
		ft_putendl_fd(input, fd1);
		free(tmp);
		free(input);
		tmp = readline("> ");
	}
	if (!input)
	{
		close_2(fd1, fd2);
		ft_putendl_fd("Minishell: here_doc:  EOF - CTL + D", 2);
		exit(1);
	}
	free(tmp);
	close(fd1);
}

void	exit_numeric_error(char *arg, t_envp *envp, int subshell)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free(envp->value);
	envp->value = ft_strdup("255");
	if (!subshell)
		exit(255);
}

void	exit_too_many_args(t_envp *envp)
{
	free(envp->value);
	envp->value = ft_strdup("1");
	ft_putendl_fd("Minishell: exit: too many arguments", 2);
}

void	exit_with_status(t_envp *envp, int status, int subshell)
{
	free(envp->value);
	envp->value = ft_itoa(status);
	if (!subshell)
		exit(status);
}
