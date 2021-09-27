#include <stdio.h>
#include <unistd.h>
#include <ulimit.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
	int c;
	extern char *optarg;
	extern int optind, optopt, opterr;

	char optstring[] = ":ispuU:cC:dvV:";

	struct rlimit rlim;

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
				if (getrlimit(RLIMIT_FSIZE, &rlim) == 0)
				{
					printf("soft file size limit of the process: %u\n", rlim.rlim_cur);
					printf("harg file size limit of the process: %u\n\n", rlim.rlim_max);
				}
				break;
			case 'U':
				break;
			case 'c':
				if (getrlimit(RLIMIT_CORE, &rlim) == 0)
				{
					printf("soft core size limit of the process: %u\n", rlim.rlim_cur);
					printf("harg core size limit of the process: %u\n\n", rlim.rlim_max);
				}
				break;
			case 'C':
				break;
			case 'd':
				char *cwd;
				size_t size = pathconf(".", _PC_PATH_MAX);

				if ((cwd = getcwd(NULL, size)) == NULL) 
				{
					perror("pwd");
				}
				else
				{
					printf("%s\n", cwd);
					free(cwd);
				}
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
