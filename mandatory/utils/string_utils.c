#include "../include/shell.h"

int	skip_spaces(const char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}
