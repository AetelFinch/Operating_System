#include <stdio.h>
#include <unistd.h>
#include <sys/types>

int main(int argc, char *argv[])
{
	int c;
	extern char *optarg;
	extern int optind, optopt, opterr;

	char optstring[] = ":ispuU:cC:dvV:";

	while ((c = getopt(argc, argv, optstring)) != -1)
	{
		switch(c)
		{
			case 'i':
				printf("real user id: %d\n", getuid());
				printf("effective user id: %d\n\n", geteuid());
				printf("real group id: %d\n", getgid());
				printf("effective group id: %d\n\n", getegid());
				break;
			case 's':
				break;
			case 'p':
				printf("process id: %d\n", getpid());
				printf("parent process id: %d\n", getppid());
				printf("process group id: %d\n\n", getpgid(0));
				break;
			case 'u':
				break;
			case 'U':
				break;
			case 'c':
				break;
			case 'C':
				break;
			case 'd':
				break;
			case 'v':
				break;
			case 'V':
				break;
			case ':':
				break;
			case '?':
				break;
		}
	}
}
