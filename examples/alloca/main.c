#include <stdio.h>
#include <alloca.h>
#include <string.h>

int main(int argc, char **argv)
{
	const size_t nelems = 4;
	const size_t elemsize = 128;
	char *alloc[nelems];

	for (size_t i = 0; i < nelems; i++) {
		if (alloc[i] = alloca(elemsize)) {
			memset(alloc[i], 0, elemsize);
		}
		printf("alloca[%d]=0x%x\n", i, alloc[i]);
	}
}
