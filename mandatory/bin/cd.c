#include "../shell.h"

void	cd(char *path)
{
	if (chdir(path) == -1)
		error("cd");
}
