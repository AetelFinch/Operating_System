#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("please, enter the file for child process\n");
		exit(1);
	}

	int status;
	switch(fork())
	{
		case 0:
			execv(argv[1], " ",  argv + 2, (char *) 0);
			exit(100);
		default:
			wait(&status);
			printf("status = %d\n", status);
			break;
	}

	return 0;
}