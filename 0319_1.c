#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){

	int filedes;
	off_t newpos;

	filedes = open("abc.txt", O_RDONLY);
	newpos = lseek(filedes, (off_t)0, SEEK_END);
	printf("Count : %ld\n", newpos - 1);
}
