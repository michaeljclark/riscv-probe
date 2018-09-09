// See LICENSE for license details.

#include "femto.h"

enum {
    SBI_CONSOLE_PUTCHAR = 1,
    SBI_CONSOLE_GETCHAR = 2,
    SBI_SHUTDOWN = 8
};

#define __asm_semihost_call(...) \
    __asm__ __volatile__ ("ecall\n\t" : "+r"(a0) : __VA_ARGS__ : "memory"); \
    return a0;

static inline long semihost_call0(long n)
{
    register long a7 __asm__("a7") = n;
    register long a0 __asm__("a0");
    __asm_semihost_call("r"(a7))
}

static inline long semihost_call1(long n, long a)
{
    register long a7 __asm__("a7") = n;
    register long a0 __asm__("a0") = a;
    __asm_semihost_call("r"(a7), "0"(a0))
}

static int semihost_getchar()
{
    semihost_call0(SBI_CONSOLE_GETCHAR);
}

static int semihost_putchar(int ch)
{
    semihost_call1(SBI_CONSOLE_PUTCHAR, ch);
}

static __attribute__((noreturn)) void semihost_poweroff()
{
    semihost_call0(SBI_SHUTDOWN);
    __builtin_unreachable();
}

console_device_t console_semihost = {
    NULL,
    semihost_getchar,
    semihost_putchar
};


poweroff_device_t poweroff_semihost = {
	NULL,
	semihost_poweroff
};
