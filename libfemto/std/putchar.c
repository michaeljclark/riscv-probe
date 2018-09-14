// See LICENSE for license details.

#include <stdio.h>
#include <device.h>

int putchar(int ch)
{
    return console_dev->putchar(ch);
}
