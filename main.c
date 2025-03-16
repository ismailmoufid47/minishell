#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void kill_all_children() {
    while (1) {
        pid_t pid = waitpid(-1, NULL, WNOHANG); // Reap any zombie child
        if (pid <= 0) {
            break;  // No more children to reap
        }
        printf("Reaped child (PID: %d)\n", pid);
    }
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: Execute `sleep 10` using execve
        printf("Child process (PID: %d) executing `sleep 10`\n", getpid());

        char *args[] = {"/bin/sleep", "10", NULL}; // Command: sleep 10
        execve(args[0], args, NULL);

        // If execve fails
        perror("execve failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process (PID: %d) created child (PID: %d)\n", getpid(), pid);
        sleep(3); // Let child run for 3 seconds

        printf("Parent sending SIGTERM to child (PID: %d)\n", pid);
        kill(pid, SIGTERM); // Send SIGTERM to child

        sleep(1); // Give time for child to exit
        kill_all_children(); // Reap the child process

        printf("All children terminated. Parent exiting.\n");
    }

    return 0;
}
