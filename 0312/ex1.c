#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){

	int fd;
	if((fd=open("data.txt", O_RDWR | O_CREAT))==-1)
	{
		printf("failed!\n");
		exit(1);
	}
	printf("fd : %d\n", fd);
	close(fd);
}
