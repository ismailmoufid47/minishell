#include "../include/shell.h"

void	handle_here_doc(char *delimiter)
{
	int		fd1;
	int		fd2;
	char	*input;

	fd1 = open_wrapper("read_line", O_WRONLY | O_TRUNC | O_CREAT, 0600);
	fd2 = open_wrapper("read_line", O_RDONLY, 0);
	unlink("read_line");
	input = readline("> ");
	while (input && ft_strcmp(input, delimiter))
	{
		ft_putendl_fd(input, fd1);
		free(input);
		input = readline("> ");
	}
	if (!input)
	{
		close_2(fd1, fd2);
		ft_putendl_fd("Minishell: here_doc:  EOF - CTL + D", 2);
		exit(1);
	}
	free(input);
	close(fd1);
	ft_dup2(fd2, 0);
}
