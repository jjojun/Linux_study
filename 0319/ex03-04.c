#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int fd1, fd2;
	ssize_t nread;
	char buffer[1024];

	fd1 = open("temp1.txt", O_RDONLY);

	if(fd1 == -1)
	{
		printf("error fd1");
		exit(1);
	}

	fd2 = open("temp2.txt", O_WRONLY | O_CREAT, 0644);

	if(fd2 == -1)
	{
		printf("error fd2");
		exit(1);
	}

	while((nread = read(fd1, buffer, 1024)) > 0)
	{
		if(write(fd2, buffer, nread) < nread)
		{
			close(fd1);
			close(fd2);
		}
	}

	close(fd1);
	close(fd2);
}
