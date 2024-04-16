#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x, y;
    int sum = 0;
    int power = 1;

    do {
        scanf("%d %d", &x, &y);
    } while (x <= 1 || x >= 11 || y <= 1 || y >= 11);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) { // Child process
        for (int i = x; i <= y; i++) {
            sum += i;
        }
    
    } else { // Parent process
        for (int i = 0; i < y; i++) {
            power *= x;
        }

        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("%d\n", power + sum);
        }
    }

    return 0;
}

