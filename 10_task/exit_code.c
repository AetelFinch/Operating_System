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

	char *arguments[argc];
	for (int i = 0; i < argc - 1; ++i)
		arguments[i] = argv[i + 1];
	arguments[argc - 1] = NULL;

	int status = 0;
	switch(fork())
	{
		case 0:
			execv(argv[1], arguments);
			exit(1);
		default:
			wait(&status);
			printf("status = %d\n", status);
			break;
	}

	return 0;
}
