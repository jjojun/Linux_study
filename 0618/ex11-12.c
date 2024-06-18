#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *msg[3] = {"apple is red\n", "banana is yellow\n", "cherry isred\n"};
    int p[2];
    pid_t pid;
    int cnt;

    if(pipe(p) == -1){
	printf("fail to call pipe()\n");
	exit(1);
    }
    if((pid = fork()) == -1){
	printf("fail to call fork()\n");
    }
    else if(pid > 0){
	printf("[parent]\n");
	close(p[0]);
	dup2(p[1], 1);
	execlp("ls", "ls", "-al", (char *)0);
	printf("[parent] fail to call execlp()\n");
    }
    else{
	printf("[child]\n");
	close(p[1]);
	dup2(p[0], 0);
	execlp("wc", "wc", (char *)0);
	printf("[child] fail to call execlp()\n");
    }
}
