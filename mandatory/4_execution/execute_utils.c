#include "../include/shell.h"

void	handle_here_doc(char *delimiter, t_envp *envp)
{
	int		fd1;
	int		fd2;
	char	*input;
	char	*tmp;

	input = "NULL";
	unlink("/tmp/read_line");
	fd1 = open_wrapper("/tmp/read_line", O_WRONLY | O_CREAT | O_TRUNC , 0600);
	fd2 = open_wrapper("/tmp/read_line", O_RDONLY, 0);
	unlink("/tmp/read_line");
	tmp = readline("> ");
	while (tmp && ft_strcmp(tmp, delimiter))
	{
		input = expand_env_variable(tmp, envp);
		ft_putendl_fd(input, fd1);
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
	ft_dup2(fd2, 0);
}

void	builtin_here_doc(char *delimiter, t_envp *envp)
{
	int		fd1;
	int		fd2;
	char	*input;
	char	*tmp;

	input = "NULL";
	fd1 = open_wrapper("read_line", O_WRONLY | O_CREAT | O_TRUNC , 0600);
	fd2 = open_wrapper("read_line", O_RDONLY, 0);
	unlink("read_line");
	tmp = readline("> ");
	while (tmp && ft_strcmp(tmp, delimiter))
	{
		input = expand_env_variable(tmp, envp);
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
