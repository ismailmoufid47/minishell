
#include "../include/shell.h"

int	open_wraper(char *file, int open_mode, int create_permissions)
{
	int	fd;

	if (!create_permissions)
		fd = open(file, open_mode);
	else
		fd = open(file, open_mode, create_permissions);
	if (fd == -1)
		error("open");
	return (fd);
}

void	cd(char *path)
{
	if (chdir(path) == -1)
		error("cd");
}
