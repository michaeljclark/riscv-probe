#pragma once

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
typedef __WCHAR_TYPE__ wchar_t;

#define NULL 0L
#define offsetof(type, member) __builtin_offsetof(type, member)
