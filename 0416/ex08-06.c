#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("[ex08-06.c] PPID : %d, PID : %d\n", getppid(), getpid());
}

