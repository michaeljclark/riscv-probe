#pragma once

#include <stdarg.h>
#include <stddef.h>

int getchar(void);
int printf(const char *, ...);
int putchar(int);
int puts(const char *);
int snprintf(char *, size_t, const char *, ...);
int vprintf(const char *, va_list);
int vsnprintf(char *, size_t, const char *, va_list);
