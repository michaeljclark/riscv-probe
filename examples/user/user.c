#include "femto.h"
#include "encoding.h"

void user_main()
{
	puts("user");
}

void switch_to_user(void (*fn)(void))
{
	write_csr(mepc, fn);
	write_csr(mstatus, set_field(read_csr(mstatus), MSTATUS_MPP, PRV_U));
	mret();
}

int main()
{
	switch_to_user(user_main);
}
