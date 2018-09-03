// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void init();
int putchar(int);
int getchar();
void poweroff(void) __attribute__((noreturn));

#ifdef __cplusplus
}
#endif
