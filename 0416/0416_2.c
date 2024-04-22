#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_CHILDREN 3

int main() {
    pid_t child_pids[MAX_CHILDREN] = {0};
    int status;

    for (int i = 0; i < MAX_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if (pid == 0) { 
            sleep(i + 1);
            printf("child%d : exit(%d)\n", i + 1, i + 1);
            exit(i + 1);
        } else { 
            child_pids[i] = pid;
        }
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        pid_t pid = child_pids[i];
        if (pid > 0) {
            waitpid(pid, &status, 0);
            printf("parent : child%d - exit(%d)\n", i + 1, WEXITSTATUS(status));
        }
    }

    return 0;
}

