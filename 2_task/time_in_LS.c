#include <stdio.h>
#include <time.h>

#define UTC_PST_HOURS_DIFF 14
#define MIN_PER_HOUR 60
#define SEC_PER_MIN 60

int main()
{
	time_t UTC_time;
	UTC_time = time(NULL);

	time_t utc_pst_diff = UTC_PST_HOURS_DIFF * MIN_PER_HOUR * SEC_PER_MIN;
	time_t PST_time = UTC_time - utc_pst_diff;

	printf("time in California: %s\n", ctime(&PST_time));

	return 0;
}