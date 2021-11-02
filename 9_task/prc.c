#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("please, enter the file for child process\n");
		exit(1);
	}

	printf("first line\n");

	int status;
	switch(fork())
	{
		case 0:
			execl("/usr/bin/cat", " ",  argv[1], (char *) 0);
			exit(100);
		default:
			wait(&status);
			printf("last line\n");
			break;
	}


	return 0;
}
