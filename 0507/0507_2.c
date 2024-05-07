#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	putenv("MYDATA=5");
	execl("env","env",(char *)0);
}
