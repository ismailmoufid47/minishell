#include <stdio.h>
#include <stdlib.h>

// test to see if child leaks even if it frees its resources
int	main(void)
{
    char	*str = strdup("hello");
    char	*str2 = strdup("world");
    int		pid;

    pid = fork();
    if (pid == 0)
    {
        printf("Child: %s %s\n", str, str2);
        free(str);
        free(str2);
        return (0);
    }
    else
    {
        wait(NULL);
        printf("Parent: %s %s\n", str, str2);
        free(str);
        free(str2);
    }
    return (0);
}