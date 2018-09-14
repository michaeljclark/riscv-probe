// See LICENSE for license details.

#include <stdio.h>
#include <device.h>

int getchar()
{
    return console_dev->getchar();
}
