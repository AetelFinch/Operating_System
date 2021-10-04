#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

extern int errno;

void check_uid(char *argv[])
{
	printf("real user id: %d\n", getuid());
	printf("effective user id: %d\n\n", geteuid());


	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		perror("can't open file\n");
		errno = 0;
	}
	else
	{
		printf("file was opened\n");
		fclose(file);
	}
}


int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("enter file\n");
		exit(1);
	}

	check_uid(argv);

	setuid(geteuid());

	check_uid(argv);

	return 0;
}
