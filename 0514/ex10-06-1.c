#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int cnt = 5;

    if ((pid = fork()) > 0) {
        sleep(2);
        kill(pid, SIGINT);
        wait(NULL); // 자식 프로세스가 종료될 때까지 기다립니다.
        printf("close\n"); // 부모 프로세스 종료 시 출력
    } else if (pid == 0) {
        while (cnt) {
            printf("[child] count is %d\n", cnt--);
            sleep(1);
        }
        printf("close\n"); // 자식 프로세스 종료 시 출력
    } else {
        printf("fail to fork\n");
    }

    return 0;
}

