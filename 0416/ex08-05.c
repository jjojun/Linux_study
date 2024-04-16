#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;

    if((pid = fork()) > 0){
	printf("[ex08-05.c] PPID : %d, PID : %d\n", getppid(), getpid());
	sleep(1);
    }
    else if(pid == 0){
	printf("[ex08-05.c] PPID : %d, PID : %d\n", getppid(), getpid());
	execl("0806", "0806", (char *)0);
    }
    else
	printf("fail to fork\n");
}
