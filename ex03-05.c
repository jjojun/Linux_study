#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	int filedes;
	off_t newpos;
	
	if((filedes = open(argv[1], O_RDONLY)) == -1)
	{
		printf("error\n");
		exit(1);
	}

	newpos = lseek(filedes, (off_t)0, SEEK_END);
	printf("file size : %ld\n", newpos);

}
