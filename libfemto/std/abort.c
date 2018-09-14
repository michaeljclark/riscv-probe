#include <stdio.h>
#include <stdlib.h>

void abort(void)
{
	puts("abort");
	exit(-1);
}
