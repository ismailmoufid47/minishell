
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

void	cd(char *path)
{
	if (chdir(path) == -1)
		error(ft_strdup("cd"));
}
