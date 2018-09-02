// See LICENSE for license details.

enum {
    SBI_SET_TIMER = 0,
    SBI_CONSOLE_PUTCHAR = 1,
    SBI_CONSOLE_GETCHAR = 2,
    SBI_CLEAR_IPI = 3,
    SBI_SEND_IPI = 4,
    SBI_REMOTE_FENCE_I = 5,
    SBI_REMOTE_SFENCE_VMA = 6,
    SBI_REMOTE_SFENCE_VMA_ASID = 7,
    SBI_SHUTDOWN = 8
};

#define __asm_semihost_call(...) \
    __asm__ __volatile__ ("ecall\n\t" : "+r"(a0) : __VA_ARGS__ : "memory"); \
    return a0;

static inline long __semihost_call0(long n)
{
    register long a7 __asm__("a7") = n;
    register long a0 __asm__("a0");
    __asm_semihost_call("r"(a7))
}

static inline long __semihost_call1(long n, long a)
{
    register long a7 __asm__("a7") = n;
    register long a0 __asm__("a0") = a;
    __asm_semihost_call("r"(a7), "0"(a0))
}

static inline long __semihost_call2(long n, long a, long b)
{
    register long a7 __asm__("a7") = n;
    register long a0 __asm__("a0") = a;
    register long a1 __asm__("a1") = b;
    __asm_semihost_call("r"(a7), "0"(a0), "r"(a1))
}

int getchar()
{
    __semihost_call0(SBI_CONSOLE_GETCHAR);
}

int putchar(int ch)
{
    __semihost_call1(SBI_CONSOLE_PUTCHAR, ch);
}

void poweroff()
{
    __semihost_call0(SBI_SHUTDOWN);
}

void init() { }
