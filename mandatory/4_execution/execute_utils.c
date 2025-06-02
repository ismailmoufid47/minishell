#include "../include/shell.h"

void	builtin_here_doc(char *delimiter, t_envp *envp)
{
	int		fd1;
	int		fd2;
	char	*input;
	char	*tmp;

	input = "NULL";
	fd1 = open_wrapper("read_line", O_W | O_C | O_T, 0600);
	fd2 = open_wrapper("read_line", O_RDONLY, 0);
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
