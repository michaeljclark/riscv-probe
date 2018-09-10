// See LICENSE for license details.

#include "femto.h"

unsigned long getauxval(unsigned long key)
{
    auxval_t *auxv = __auxv;
    while(auxv->key) {
        if (auxv->key == key) {
            return auxv->val;
        }
        auxv++;
    }
    return 0;
}
