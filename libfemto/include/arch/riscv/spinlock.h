// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Ticket Lock
 *
 * Author: Michael Clark <michaeljclark@mac.com>
 *
 * Ticket locks are fair spinlocks that order acccess on a first-in,
 * first-out basis. The lock is composed of a head counter and a tail
 * counter. The head counter indicates the ticket number of the current
 * lock owner. The tail counter indicates the last issued ticket number.
 * To acquire the lock, the acquiring thread atomically increments the
 * tail counter to assign itself a ticket number. It then waits until
 * its assigned ticket number is seen in the head counter. If the lock
 * is not contended, then head will equal the ticket number just assigned.
 * To release the lock, the lock owner atomically increments head counter
 * thereby allowing access to the thread holding the next ticket number.
 *
 * Initialializtion - the lock is initialized unlocked, so that the
 * next tail increment returns a ticket that will acquire the lock.
 *
 *   tail   | head
 *   -------|-------
 *   0x0000 | 0x0001
 *
 * Lock - the tail is incremented, and the thread waits unti the tail
 * is equal to the head before returning control, which is the typical
 * case if the lock is uncontended.
 *
 *   tail   | head
 *   -------|-------
 *   0x0001 | 0x0001
 *
 * Unlock - the head is incremented, so that it will now equal the value
 * of the ticket of the next waiter, if any.
 *
 *   tail   | head
 *   -------|-------
 *   0x0001 | 0x0002
 *
 * Waiters - the number of waiters can be calculated by subtracting
 * head (current ticket) from the tail plus one (next ticket)
 *
 *   num_waiters = tail + 1 - head
 */

/**
 * Ticket lock types
 */

typedef unsigned short ticket_t;
typedef unsigned int ticketdata_t;

typedef struct {
    volatile ticketdata_t data;
} spinlock_t;

#define TICKET_SHIFT ((sizeof(ticketdata_t) / sizeof(ticket_t)) * 8)

/**
 * Ticket lock encode
 */
static inline ticketdata_t ticketlock_data(ticket_t tail, ticket_t head)
{
    return (((ticketdata_t)tail) << TICKET_SHIFT) | (ticketdata_t)head;
}

/**
 * Ticket lock tail
 */
static inline ticket_t ticketlock_tail(ticketdata_t data) { return data >> 16; }

/**
 * Ticket lock head
 */
static inline ticket_t ticketlock_head(ticketdata_t data) { return data; }

/**
 * Ticket lock initializer
 */
#define SPINLOCK_INIT (spinlock_t){1};

/**
 * load reserved acquire
 *
 * \param pvalue pointer to word to load from
 * \return loaded value
 */
static inline unsigned int _lr_aq_w(volatile unsigned int *pvalue)
{
    unsigned int value;
    asm volatile (
          "lr.w.aq %0, %1"
        : "=&r"(value), "+A"(*pvalue));
    return value;
}

/**
 * store conditional release
 *
 * \param pvalue pointer to word to store to
 * \param value word to write
 * \return true for failure
 */
static inline int _sc_rl_w(volatile unsigned int *pvalue, unsigned int value)
{
    int result;
    asm volatile (
          "sc.w.rl %0, %2, %1"
        : "=&r"(result), "+A"(*pvalue)
        : "r"(value)
        : "memory"
    );
    return result;
}

/**
 * load acquire
 *
 * \param pvalue pointer to word to load from
 * \return loaded value
 */
static inline unsigned int _l_aq_w(volatile unsigned int *pvalue)
{
    unsigned int result;
    asm volatile (
          "lw %0, %1\n"
          "fence r,rw"
        : "=&r"(result), "+A"(*pvalue)
    );
    return result;
}

/**
 * barrier acquire
 *
 * order subsequent modifications after prior lock reads
 *
 *   <read lock>
 *   _barrier_acquire();
 */
static inline void _barrier_acquire() { asm volatile ("fence r,rw"); }

/**
 * barrier release
 *
 * order prior modifications before subsequent lock write
 *
 *   _barrier_release();
 *   <write lock>
 */
static inline void _barrier_release() { asm volatile ("fence rw,w"); }

/**
 * spinlock lock
 *
 * \param lock pointer to lock
 */
void spinlock_lock(spinlock_t *lock);

/**
 * spinlock trylock
 *
 * \param lock pointer to lock
 * \return non zero if lock was successfully taken
 */
int spinlock_trylock(spinlock_t *lock);

/**
 * spinlock unlock
 *
 * \param lock pointer to lock
 */
void spinlock_unlock(spinlock_t *lock);

/**
 * spinlock waiters
 *
 * \param lock pointer to lock
 * \return number of waiters
 */
int spinlock_waiters(spinlock_t *lock);

#ifdef __cplusplus
}
#endif
