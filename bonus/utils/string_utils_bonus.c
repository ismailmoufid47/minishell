#include "../include/shell_bonus.h"

int	skip_spaces(const char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}
