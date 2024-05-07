#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

int main(){
	pid_t pid;

	if((pid = fork())>0){
		sleep(1);
		exit(1);
	}
	else if(pid==0)
	{
		while(1){
			int fd;
			time_t t = time(NULL);
			fd = open("curtime.txt",O_RDWR|O_CREAT,0644);
			char* buf = ctime(&t);
			write(fd,buf,strlen(buf));
			close(fd);
			setsid();
			sleep(10);
		}
	}
}
