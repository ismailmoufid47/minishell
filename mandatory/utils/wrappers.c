
#include "../include/shell.h"

void	pipe_wrapper(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		error(ft_strdup("pipe"));
}

int	open_wrapper(char *file, int open_mode, int create_permissions)
{
	int	fd;

	if (!create_permissions)
		fd = open(file, open_mode);
	else
		fd = open(file, open_mode, create_permissions);
	if (fd == -1)
		error(ft_strdup("open"));
	return (fd);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		error(ft_strdup("dup2"));
	close(fd1);
}

void	close_2(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

char	**split_zayda_naghza(char *full_cmd)
{
	int		i;
	char	**tokens;

	i = 0;
	tokens = tokenize(full_cmd);
	while (tokens[i])
	{
		if (tokens[i][0] == '\'' || tokens[i][0] == '"')
		{
			if (tokens[i][0] == tokens[i][ft_strlen(tokens[i]) - 1])
				tokens[i][ft_strlen(tokens[i]) - 1] = 0;
			tokens[i] = &tokens[i][1];
		}
		i++;
	}
	return (tokens);
}
