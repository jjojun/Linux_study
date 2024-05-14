#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    int cnt = 5;

    if((pid = fork()) > 0){
	sleep(2);
	kill(pid, SIGINT);
	raise(SIGINT);
	printf("[parent] bye!\n");
    }
    else if(pid == 0){
    while(cnt){
	printf("[child] count is %d\n", cnt--);
	sleep(1);
    }
    }
    else
	printf("fail to fork\n");
}    
