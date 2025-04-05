#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(){
    int fd = open("|", O_APPEND, O_CREAT);
    printf("%d\n", fd);
}

