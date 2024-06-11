#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num1, num2;
    int add_result, multiply_result;
    int pipe_add[2], pipe_multiply[2];
    pid_t add_pid, multiply_pid;

    if (pipe(pipe_add) == -1 || pipe(pipe_multiply) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    add_pid = fork();
    if (add_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (add_pid == 0) {
        close(pipe_add[0]);
        write(pipe_add[1], &num1, sizeof(int));
        write(pipe_add[1], &num2, sizeof(int));
        close(pipe_add[1]);
        exit(EXIT_SUCCESS);
    }

    multiply_pid = fork();
    if (multiply_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (multiply_pid == 0) {
        close(pipe_multiply[0]);
        write(pipe_multiply[1], &num1, sizeof(int));
        write(pipe_multiply[1], &num2, sizeof(int));
        close(pipe_multiply[1]);
        exit(EXIT_SUCCESS);
    }

    close(pipe_add[1]);
    close(pipe_multiply[1]);

    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    wait(NULL);
    wait(NULL);

    write(pipe_add[0], &num1, sizeof(int));
    write(pipe_add[0], &num2, sizeof(int));
    write(pipe_multiply[0], &num1, sizeof(int));
    write(pipe_multiply[0], &num2, sizeof(int));

    close(pipe_add[0]);
    close(pipe_multiply[0]);

    read(pipe_add[0], &add_result, sizeof(int));
    read(pipe_multiply[0], &multiply_result, sizeof(int));

    printf("Final result: %d\n", add_result + multiply_result);

    return 0;
}

