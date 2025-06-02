#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	error(char *error_prefix)
{
	
	perror(error_prefix);
	free(error_prefix);
	exit(EXIT_FAILURE);
}


int	open_wrapper(char *file, int open_mode, int create_permissions)
{
	int	fd;

	if (!create_permissions)
		fd = open(file, open_mode);
	else
		fd = open(file, open_mode, create_permissions);
	if (fd == -1)
		error(file);
	return (fd);
}

// test to see if child leaks even if it frees its resources
int	main(void)
{
    int i = 0;
    char *file = "ff";
    char buf[10] = {0};
    while (i < 3)
    {
        unlink(file);
        int fd1 = open_wrapper(file, O_W | O_C | O_T, 0666);
        int fd2 = open_wrapper(file , O_RDONLY, 0);
        close(fd1);
        read(fd2, buf, 10);
        i++;
    }
    
    return (0);
}
