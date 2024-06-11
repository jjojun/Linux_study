#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    int num1, num2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("First Num : ");
    scanf("%d", &num1);
    printf("Second Num : ");
    scanf("%d", &num2);

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fd[1]);

        int sum;
        read(fd[0], &sum, sizeof(sum));
        close(fd[0]);

        printf("Sum : %d\n", sum);

        exit(EXIT_SUCCESS);
    } else {
        close(fd[0]);

        int sum = num1 + num2;
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);

        wait(NULL);
    }

    return 0;
}

