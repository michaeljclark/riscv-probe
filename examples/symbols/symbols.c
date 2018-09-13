#include <stdio.h>

/* program to print linker script provided symbols */

extern char _text_start;
extern char _text_end;
extern char _rodata_start;
extern char _rodata_end;
extern char _data_start;
extern char _data_end;
extern char _bss_start;
extern char _bss_end;
extern char _memory_start;
extern char _memory_end;

int main(int argc, char **argv)
{
	printf("_text_start=0x%x\n", &_text_start);
	printf("_text_end=0x%x\n", &_text_end);
	printf("_rodata_start=0x%x\n", &_rodata_start);
	printf("_rodata_end=0x%x\n", &_rodata_end);
	printf("_data_start=0x%x\n", &_data_start);
	printf("_data_end=0x%x\n", &_data_end);
	printf("_bss_start=0x%x\n", &_bss_start);
	printf("_bss_end=0x%x\n", &_bss_end);
	printf("_memory_start=0x%x\n", &_memory_start);
	printf("_memory_end=0x%x\n", &_memory_end);
}
