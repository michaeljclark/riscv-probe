// See LICENSE for license details.

#include <arch/riscv/spinlock.h>

/**
 * spinlock lock
 *
 * \param lock pointer to lock
 *
 *     lui     a2,0x10
 *  1: lr.w.aq a4,(a0)
 *     addw    a5,a2,a4
 *     sc.w.rl a3,a5,(a0)
 *     bnez    a4,1b
 *     srliw   a4,a5,0x10
 *     fence   r,rw
 * 2:  slliw   a5,a5,0x10
 *     srliw   a5,a5,0x10
 *     bne     a5,a4,3f
 *     ret
 * 3:  lw      a5,0(a0)
 *     fence   r,rw
 *     j       2b
 */

void spinlock_lock(spinlock_t *lock)
{
    ticketdata_t ld;
    ticket_t ticket_num;

    /* increment tail to acquire a ticket number */
    do {
        ld = _lr_aq_w(&lock->data) + ((ticketdata_t)1 << TICKET_SHIFT);
    } while (_sc_rl_w(&lock->data, ld));

    /* fetch our ticket number */
    ticket_num = ticketlock_tail(ld);

    /* subsequent modifications are ordered after lock read */
    _barrier_acquire();

    /* wail until our ticket number is head */
    while (ticketlock_head(ld) != ticket_num) {
        ld = _l_aq_w(&lock->data);
    }
}

/**
 * spinlock trylock
 *
 * \param lock pointer to lock
 * \return non zero if lock was successfully taken
 *
 *     lui     a5,0x10
 *     lr.w.aq a4,(a0)
 *     addw    a5,a5,a4
 *     slliw   a3,a5,0x10
 *     srliw   a3,a3,0x10
 *     srliw   a4,a5,0x10
 *     beq     a3,a4,2f
 * 1:  li      a0,0
 *     ret
 * 2:  sc.w.rl a4,a5,(a0)
 *     bnez    a4,1b
 *     fence   r,rw
 *     li      a0,1
 *     ret
 */

int spinlock_trylock(spinlock_t *lock)
{
    ticketdata_t ld;
    ticket_t ticket_num;
    int result;

    /* increment tail to the next ticket number */
    ld = _lr_aq_w(&lock->data) + ((ticketdata_t)1 << TICKET_SHIFT);
    ticket_num = ticketlock_tail(ld);

    /* return true if our ticket is next and lock update succeeded */
    result = ticketlock_head(ld) == ticket_num && !_sc_rl_w(&lock->data, ld);

    if (result) {
        /* subsequent modifications are ordered after lock read */
        _barrier_acquire();
    }

    return result;
}

/**
 * spinlock unlock
 *
 * \param lock pointer to lock
 *
 *     fence   rw,w
 * 1:  lr.w.aq a4,(a0)
 *     srliw   a5,a4,0x10
 *     addiw   a4,a4,1
 *     slliw   a4,a4,0x10
 *     srliw   a4,a4,0x10
 *     slliw   a5,a5,0x10
 *     or      a5,a5,a4
 *     sc.w.rl a4,a5,(a0)
 *     bnez    a5,1b
 *     ret
 */
void spinlock_unlock(spinlock_t *lock)
{
    ticketdata_t ld;

    /* prior modifications are ordered before lock write */
    _barrier_release();

    /* increment head to release lock to the next ticket holder */
    do {
        ld = _lr_aq_w(&lock->data);
        ld = ticketlock_data(ticketlock_tail(ld), ticketlock_head(ld) + 1);
    } while (_sc_rl_w(&lock->data, ld));
}

/**
 * spinlock waiters
 *
 * \param lock pointer to lock
 * \return number of waiters
 *
 *     lw      a5,0(a0)
 *     fence   r,rw
 *     srliw   a0,a5,0x10
 *     slliw   a5,a5,0x10
 *     srliw   a5,a5,0x10
 *     subw    a0,a0,a5
 *     addiw   a0,a0,1
 *     ret
 */
int spinlock_waiters(spinlock_t *lock)
{
    ticketdata_t ld = _l_aq_w(&lock->data);

    return (int)ticketlock_tail(ld) - (int)ticketlock_head(ld) + 1;
}
