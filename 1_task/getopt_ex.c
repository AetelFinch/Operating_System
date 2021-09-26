#include <stdio.h>
#include <unistd.h>
<<<<<<< Updated upstream
#include <ulimit.h>
#include <sys/types.h>

=======
#include <sys/types.h>
>>>>>>> Stashed changes

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
				struct rlimit rlim;
				if (getrlimit(RLIMIT_FSIZE, &rlim) == 0)
				{
					print("soft file size limit of the process: %d\n", rlim.rlim_cur);
					print("harg file size limit of the process: %d\n\n", rlim.rlim_max);
				}
				break;
			case 'U':
				break;
			case 'c':
				struct rlimit rlim;
				if (getrlimit(RLIMIT_CORE, &rlim) == 0)
				{
					print("soft core size limit of the process: %d\n", rlim.rlim_cur);
					print("harg core size limit of the process: %d\n\n", rlim.rlim_max);
				}
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
