// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include <device.h>

void exit(int status)
{
    poweroff_dev->poweroff(status);
    asm volatile("1: j 1b");
    __builtin_unreachable();
}
