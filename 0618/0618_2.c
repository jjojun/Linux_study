#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num1, num2;
    int sum, product;
    int fd1[2], fd2[2];
    pid_t pid1, pid2;

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("Input two num : ");
    scanf("%d %d", &num1, &num2);

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(fd1[0]);
        sum = num1 + num2;
        write(fd1[1], &sum, sizeof(sum));
        close(fd1[1]);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        close(fd2[0]);
        product = num1 * num2;
        write(fd2[1], &product, sizeof(product));
        close(fd2[1]);
        exit(0);
    }

    close(fd1[1]);
    close(fd2[1]);

    read(fd1[0], &sum, sizeof(sum));
    close(fd1[0]);

    read(fd2[0], &product, sizeof(product));
    close(fd2[0]);

    wait(NULL);
    wait(NULL);

    printf("result : %d\n", sum + product);

    return 0;
}

