#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 16

void onerror(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int p1[2], p2[2], p3[2];
    char msg[MSGSIZE];
    pid_t pid1, pid2, pid3;

    if (pipe(p1) == -1)
        onerror("fail to call pipe() #1\n");
    if (pipe(p2) == -1)
        onerror("fail to call pipe() #2\n");
    if (pipe(p3) == -1)
        onerror("fail to call pipe() #3\n");

    if ((pid1 = fork()) == -1)
        onerror("fail to call fork() #1\n");

    if (pid1 > 0 && (pid2 = fork()) == -1)
        onerror("fail to call fork() #2\n");

    if (pid1 > 0 && pid2 > 0 && (pid3 = fork()) == -1)
        onerror("fail to call fork() #3\n");

    if (pid1 > 0 && pid2 > 0 && pid3 > 0) {
        close(p1[1]);
        close(p2[1]);
        close(p3[1]);

        printf("parent: %d\n", getpid());

        for (int i = 0; i < 3; i++) {
            if (read(p1[0], msg, MSGSIZE) > 0)
                printf("[parent] %s from child1\n", msg);

            if (read(p2[0], msg, MSGSIZE) > 0)
                printf("[parent] %s from child2\n", msg);

            if (read(p3[0], msg, MSGSIZE) > 0)
                printf("[parent] %s from child3\n", msg);
        }

        close(p1[0]);
        close(p2[0]);
        close(p3[0]);

        wait(NULL);
        wait(NULL);
        wait(NULL);

    } else if (pid1 == 0) {
        close(p1[0]);
        for (int i = 0; i < 3; i++) {
            sleep(i + 1);
            write(p1[1], "i am child1", MSGSIZE);
        }
        close(p1[1]);
        exit(0);

    } else if (pid2 == 0) {
        close(p2[0]);
        for (int i = 0; i < 3; i++) {
            sleep((i + 3) % 4);
            write(p2[1], "i am child2", MSGSIZE);
        }
        close(p2[1]);
        exit(0);

    } else if (pid3 == 0) {
        close(p3[0]);
        for (int i = 0; i < 3; i++) {
            sleep(i + 4);
            write(p3[1], "i am child3", MSGSIZE);
        }
        close(p3[1]);
        exit(0);
    }

    return 0;
}

