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
				break;
			case 's':
				break;
			case 'p':
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
