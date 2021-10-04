#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

extern int errno;

void check_uid()
{
	printf("real user id: %d\n", getuid());
	printf("effective user id: %d\n\n", geteuid());


	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		perror("can't open file");
		errno = 0;
	}
	else
	{
		print("file was opened");
		fclose(file);
	}
}


int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("enter file");
		exit(1);
	}

	check_uid();

	setuid(geteuid());

	check_uid();

	return 0;
}