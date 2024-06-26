#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ulimit.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
	int c;
	extern int errno;
	extern char *optarg;
	extern int optind, optopt, opterr;

	char optstring[] = ":ispuU:cC:dvV:";

	struct rlimit rlim;
	char *cwd;

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
				setpgid(getpid(), 0);
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
				if (getrlimit(RLIMIT_FSIZE, &rlim) == 0)
				{
					rlim.rlim_cur = atol(optarg);
					if (errno != 0)
					{
						fprintf(stderr, "incorrect value for -U option\n\n");
						break;
					}
					if (setrlimit(RLIMIT_FSIZE, &rlim))
						fprintf(stderr, "incorrect value for -U option\n\n");
				}
				break;
			case 'c':
				if (getrlimit(RLIMIT_CORE, &rlim) == 0)
				{
					printf("soft core size limit of the process: %u\n", rlim.rlim_cur);
					printf("harg core size limit of the process: %u\n\n", rlim.rlim_max);
				}
				break;
			case 'C':
				if (getrlimit(RLIMIT_CORE, &rlim) == 0)
				{
					rlim.rlim_cur = atol(optarg);
					setrlimit(RLIMIT_CORE, &rlim);
				}
				break;
			case 'd':
				if ((cwd = getcwd(NULL, pathconf(".", _PC_PATH_MAX))) == NULL) 
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
				printf("PATH: %s\n", getenv("HOME"));
				printf("TERM: %s\n", getenv("TERM"));
				printf("TZ: %s\n", getenv("TZ"));
				printf("HOME: %s\n", getenv("HOME"));
				printf("USER: %s\n\n", getenv("USER"));
				break;
			case 'V':
				putenv(optarg);
				break;
			case ':':
				fprintf(stderr, "Option -%c requires an operand\n", optopt);
				break;
			case '?':
				fprintf(stderr, "Unrecognized option: -%c\n", optopt);
				break;
		}
		errno = 0;
	}
}
