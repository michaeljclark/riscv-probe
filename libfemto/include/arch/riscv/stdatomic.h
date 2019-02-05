// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
 * We use the GCC implementation of __atomic_is_lock_free
 */

#define atomic_is_lock_free(obj) \
    __atomic_is_lock_free(sizeof(obj), obj)

/*
 * GCC Built-in Atomics (not enabled by default, because they are buggy)
 */

#if defined(LIBFEMTO_USE_GCC_BUILTINS)

#define atomic_flag_test_and_set(obj) \
    __atomic_test_and_set(obj, __ATOMIC_SEQ_CST)
#define atomic_flag_test_and_set_explicit(obj, order) \
    __atomic_test_and_set(obj, order)

#define atomic_flag_clear(obj) \
    __atomic_test_and_set(obj, __ATOMIC_SEQ_CST)
#define atomic_flag_clear_explicit(obj, order) \
    __atomic_test_and_set(obj, order)

#define atomic_thread_fence(order) \
    __atomic_thread_fence(order)

#define atomic_signal_fence(order) \
    __atomic_signal_fence(order)

#define atomic_store(obj, desired) \
    __atomic_store_n(obj, desired, __ATOMIC_SEQ_CST)
#define atomic_store_explicit(obj, desired, order) \
    __atomic_store_n(obj, desired, order)

#define atomic_load(obj) \
    __atomic_load_n(obj, __ATOMIC_SEQ_CST)
#define atomic_load_explicit(obj,order) \
    __atomic_load_n(obj,order)

#define atomic_exchange(obj, desired) \
    __atomic_exchange_n(obj, desired, __ATOMIC_SEQ_CST)
#define atomic_exchange_explicit(obj, desired, order) \
    __atomic_exchange_n(obj, desired, order)

#define atomic_compare_exchange_strong(obj, expected, desired) \
    __atomic_compare_exchange_n(obj, expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_strong_explicit(obj, expected, desired, succ, fail) \
    __atomic_compare_exchange_n(obj, expected, desired, 0, succ, fail)

#define atomic_compare_exchange_weak(obj, expected, desired) \
    __atomic_compare_exchange_n(obj, expected, desired, 1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_weak_explicit(obj, expected, desired, succ, fail) \
    __atomic_compare_exchange_n(obj, expected, desired, 1, succ, fail)

#define atomic_fetch_add(obj, arg) \
    __atomic_fetch_add(obj, arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(obj, arg, order) \
    __atomic_fetch_add(obj, arg, order)

#define atomic_fetch_sub(obj, arg) \
    __atomic_fetch_sub(obj, arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(obj, arg, order) \
    __atomic_fetch_sub(obj, arg, order)

#define atomic_fetch_or(obj, arg) \
    __atomic_fetch_or(obj, arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(obj, arg, order) \
    __atomic_fetch_or(obj, arg, order)

#define atomic_fetch_xor(obj, arg) \
    __atomic_fetch_xor(obj, arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(obj, arg, order) \
    __atomic_fetch_xor(obj, arg, order)

#define atomic_fetch_and(obj, arg) \
    __atomic_fetch_and(obj, arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(obj, arg, order) \
    __atomic_fetch_and(obj, arg, order)
#endif

#elif defined(__riscv)

/*
 * atomic_load
 */

#define __atomic_load_asm(obj, ASM_BARRIER, ASM_ACQUIRE)            \
__extension__ ({                                                    \
    __typeof__(obj) __obj = (obj);                                  \
    __typeof__(*(obj)) __result;                                    \
    switch (sizeof(__typeof__(*obj))) {                             \
    case 1:                                                         \
        __asm__ volatile (                                          \
              ASM_BARRIER "\n" "lb %0, %1\n" ASM_ACQUIRE            \
            : "=&r"(__result), "+A"(*__obj)                         \
        );                                                          \
        break;                                                      \
    case 2:                                                         \
        __asm__ volatile (                                          \
              ASM_BARRIER "\n" "lh %0, %1\n" ASM_ACQUIRE            \
            : "=&r"(__result), "+A"(*__obj)                         \
        );                                                          \
        break;                                                      \
    case 4:                                                         \
        __asm__ volatile (                                          \
              ASM_BARRIER "\n" "lw %0, %1\n" ASM_ACQUIRE            \
            : "=&r"(__result), "+A"(*__obj)                         \
        );                                                          \
        break;                                                      \
    case 8:                                                         \
        if (__riscv_xlen < 64) __builtin_unreachable();             \
        __asm__ volatile (                                          \
              ASM_BARRIER "\n" "ld %0, %1\n" ASM_ACQUIRE            \
            : "=&r"(__result), "+A"(*__obj)                         \
        );                                                          \
        break;                                                      \
    }                                                               \
    __result;                                                       \
})

#define __atomic_load_relaxed(obj) \
    __atomic_load_asm(obj, "", "")

#define __atomic_load_acquire(obj) \
    __atomic_load_asm(obj, "", "fence r,rw")

#define __atomic_load_seq_cst(obj) \
    __atomic_load_asm(obj, "fence rw,rw", "fence r,rw")

#define atomic_load_explicit(obj, order)                            \
__extension__ ({                                                    \
    __typeof__(*(obj)) __result;                                    \
    switch (order) {                                                \
    case __ATOMIC_ACQUIRE:                                          \
        __result = __atomic_load_acquire(obj) ; break;              \
    case __ATOMIC_SEQ_CST:                                          \
        __result = __atomic_load_seq_cst(obj) ; break;              \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __result = __atomic_load_relaxed(obj) ; break;              \
    }                                                               \
    __result;                                                       \
})

#define atomic_load(obj) \
    atomic_load_explicit(obj, __ATOMIC_SEQ_CST)

/*
 * atomic_store
 */

#define __atomic_store_asm(obj, value, ASM_RELEASE)                 \
__extension__ ({                                                    \
    __typeof__(obj) __obj = (obj);                                  \
    __typeof__(*(obj)) __value = (value);                           \
    switch (sizeof(__typeof__(*obj))) {                             \
    case 1:                                                         \
        __asm__ volatile (                                          \
            ASM_RELEASE "\n" "sb %1, %0\n"                          \
            : "+A"(*__obj) : "r"(__value) : "memory"                \
        );                                                          \
        break;                                                      \
    case 2:                                                         \
        __asm__ volatile (                                          \
            ASM_RELEASE "\n" "sh %1, %0\n"                          \
            : "+A"(*__obj) : "r"(__value) : "memory"                \
        );                                                          \
        break;                                                      \
    case 4:                                                         \
        __asm__ volatile (                                          \
            ASM_RELEASE "\n" "sw %1, %0\n"                          \
            : "+A"(*__obj) : "r"(__value) : "memory"                \
        );                                                          \
        break;                                                      \
    case 8:                                                         \
        if (__riscv_xlen < 64) __builtin_unreachable();             \
        __asm__ volatile (                                          \
            ASM_RELEASE "\n" "sd %1, %0\n"                          \
            : "+A"(*__obj) : "r"(__value) : "memory"                \
        );                                                          \
        break;                                                      \
    }                                                               \
})

#define __atomic_store_relaxed(obj, value) \
    __atomic_store_asm(obj, value, "")

#define __atomic_store_release(obj, value) \
    __atomic_store_asm(obj, value, "fence rw,w")

#define __atomic_store_seq_cst(obj, value) \
    __atomic_store_asm(obj, value, "fence rw,w")


#define atomic_store_explicit(obj, value, order)                    \
__extension__ ({                                                    \
    switch (order) {                                                \
    case __ATOMIC_RELEASE:                                          \
        __atomic_store_release(obj, value) ; break;                 \
    case __ATOMIC_SEQ_CST:                                          \
        __atomic_store_seq_cst(obj, value) ; break;                 \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __atomic_store_relaxed(obj, value) ; break;                 \
    }                                                               \
})

#define atomic_store(obj, value) \
    atomic_store_explicit(obj, value, __ATOMIC_SEQ_CST)

/*
 * atomic_compare_exchange
 */

#define __atomic_cmpxchg_asm(obj, exp, val, ASM_AQ, ASM_RL)         \
__extension__ ({                                                    \
    __typeof__(obj) __obj = (obj);                                  \
    __typeof__(*(obj)) __exp = (exp);                               \
    __typeof__(*(obj)) __val = (val);                               \
    __typeof__(*(obj)) __result;                                    \
    register unsigned int __ret;                                    \
    switch (sizeof(__typeof__(*obj))) {                             \
    case 1:                                                         \
    case 2:                                                         \
        __builtin_unreachable();                                    \
        break;                                                      \
    case 4:                                                         \
        __asm__ volatile (                                          \
              "0:  lr.w" ASM_AQ " %0, %2\n"                         \
              "    bne  %0, %z3, 1f\n"                              \
              "    sc.w" ASM_RL " %1, %z4, %2\n"                    \
              "    bnez %1, 0b  \n" /* always strong */             \
              "1:\n"                                                \
            : "=&r"(__result), "=&r" (__ret), "+A"(*__obj)          \
            : "r"(__exp), "r"(__val)                                \
            : "memory"                                              \
        );                                                          \
        break;                                                      \
    case 8:                                                         \
        if (__riscv_xlen < 64) __builtin_unreachable();             \
        __asm__ volatile (                                          \
              "0:  lr.d" ASM_AQ " %0, %2\n"                         \
              "    bne  %0, %z3, 1f\n"                              \
              "    sc.d" ASM_RL " %1, %z4, %2\n"                    \
              "    bnez %1, 0b  \n" /* always strong */             \
              "1:\n"                                                \
            : "=&r"(__result), "=&r" (__ret), "+A"(*__obj)          \
            : "r"(__exp), "r"(__val)                                \
            : "memory"                                              \
        );                                                          \
        break;                                                      \
    }                                                               \
    __result;                                                       \
})

#define __atomic_cmpxchg_relaxed(obj, exp, val) \
    __atomic_cmpxchg_asm(obj, exp, val, "", "")

#define __atomic_cmpxchg_acquire(obj, exp, val) \
    __atomic_cmpxchg_asm(obj, exp, val, ".aq", "")

#define __atomic_cmpxchg_release(obj, exp, val) \
    __atomic_cmpxchg_asm(obj, exp, val, "", ".rl")

#define __atomic_cmpxchg_acq_rel(obj, exp, val) \
    __atomic_cmpxchg_asm(obj, exp, val, ".aq", ".rl")

#define __atomic_cmpxchg_seq_cst(obj, exp, val) \
    __atomic_cmpxchg_asm(obj, exp, val, ".aqrl", ".rl")

#define __atomic_cmpxchg_strong(obj, exp, val, succ, fail)          \
__extension__ ({                                                    \
    __typeof__(*(obj)) __result;                                    \
    switch (succ) {                                                 \
    case __ATOMIC_ACQUIRE:                                          \
    case __ATOMIC_CONSUME: /* promote to acquire for now */         \
        __result = __atomic_cmpxchg_acquire(obj, exp, val); break;  \
    case __ATOMIC_RELEASE:                                          \
        __result = __atomic_cmpxchg_release(obj, exp, val); break;  \
    case __ATOMIC_ACQ_REL:                                          \
        __result = __atomic_cmpxchg_acq_rel(obj, exp, val); break;  \
    case __ATOMIC_SEQ_CST:                                          \
        __result = __atomic_cmpxchg_seq_cst(obj, exp, val); break;  \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __result = __atomic_cmpxchg_relaxed(obj, exp, val); break;  \
    }                                                               \
    __result;                                                       \
})

#define atomic_compare_exchange_strong(obj, exp, val) \
    __atomic_cmpxchg_strong(obj, exp, val, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_strong_explicit(obj, exp, val, succ, fail) \
    __atomic_cmpxchg_strong(obj, exp, val, succ, fail)

#define atomic_compare_exchange_weak(obj, exp, val) \
    __atomic_cmpxchg_strong(obj, exp, val, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_weak_explicit(obj, exp, val, succ, fail) \
    __atomic_cmpxchg_strong(obj, exp, val, succ, fail)

/*
 * atomic_op template
 */

#define __atomic_op_asm(AMO_OP, obj, arg, ASM_AQRL)                 \
__extension__ ({                                                    \
    __typeof__(obj) __obj = (obj);                                  \
    __typeof__(*(obj)) __arg = (arg);                               \
    __typeof__(*(obj)) __result;                                    \
    switch (sizeof(__typeof__(*obj))) {                             \
    case 1:                                                         \
    case 2:                                                         \
        __builtin_unreachable();                                    \
        break;                                                      \
    case 4:                                                         \
        __asm__ volatile (                                          \
              AMO_OP ".w" ASM_AQRL " %0, %2, %1\n"                  \
            : "=&r"(__result), "+A"(*__obj)                         \
            : "r"(__arg)                                            \
            : "memory"                                              \
        );                                                          \
        break;                                                      \
    case 8:                                                         \
        if (__riscv_xlen < 64) __builtin_unreachable();             \
        __asm__ volatile (                                          \
              AMO_OP ".d" ASM_AQRL " %0, %2, %1\n"                  \
            : "=&r"(__result), "+A"(*__obj)                         \
            : "r"(__arg)                                            \
            : "memory"                                              \
        );                                                          \
        break;                                                      \
    }                                                               \
    __result;                                                       \
})

#define __atomic_op_relaxed(op, obj, arg) \
    __atomic_op_asm(op, obj, arg, "")

#define __atomic_op_acquire(op, obj, arg) \
    __atomic_op_asm(op, obj, arg, ".aq")

#define __atomic_op_release(op, obj, arg) \
    __atomic_op_asm(op, obj, arg, ".rl")

#define __atomic_op_acq_rel(op, obj, arg) \
    __atomic_op_asm(op, obj, arg, ".aqrl")

#define __atomic_op_seq_cst(op, obj, arg) \
    __atomic_op_asm(op, obj, arg, ".aqrl")

#define __atomic_op(op, obj, arg, order)                            \
__extension__ ({                                                    \
    __typeof__(*(obj)) __result;                                    \
    switch (order) {                                                \
    case __ATOMIC_ACQUIRE:                                          \
    case __ATOMIC_CONSUME: /* promote to acquire for now */         \
        __result = __atomic_op_acquire(op, obj, arg); break;        \
    case __ATOMIC_RELEASE:                                          \
        __result = __atomic_op_release(op, obj, arg); break;        \
    case __ATOMIC_ACQ_REL:                                          \
        __result = __atomic_op_acq_rel(op, obj, arg); break;        \
    case __ATOMIC_SEQ_CST:                                          \
        __result = __atomic_op_seq_cst(op, obj, arg); break;        \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __result = __atomic_op_relaxed(op, obj, arg); break;        \
    }                                                               \
    __result;                                                       \
})

/*
 * atomic_exchange
 */

#define atomic_exchange(obj, arg) \
    __atomic_op("amoswap", obj, arg, __ATOMIC_SEQ_CST)
#define atomic_exchange_explicit(obj, arg, order) \
    __atomic_op("amoswap", obj, arg, order)

/*
 * atomic_fetch_add
 */

#define atomic_fetch_add(obj, arg) \
    __atomic_op("amoadd", obj, arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(obj, arg, order) \
    __atomic_op("amoadd", obj, arg, order)

/*
 * atomic_fetch_sub
 */

#define atomic_fetch_sub(obj, arg) \
    __atomic_op("amoadd", obj, -arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(obj, arg, order) \
    __atomic_op("amoadd", obj, -arg, order)

/*
 * atomic_fetch_or
 */

#define atomic_fetch_or(obj, arg) \
    __atomic_op("amoor", obj, -arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(obj, arg, order) \
    __atomic_op("amoor", obj, -arg, order)

/*
 * atomic_fetch_xor
 */

#define atomic_fetch_xor(obj, arg) \
    __atomic_op("amoxor", obj, -arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(obj, arg, order) \
    __atomic_op("amoxor", obj, -arg, order)

/*
 * atomic_fetch_and
 */

#define atomic_fetch_and(obj, arg) \
    __atomic_op("amoand", obj, -arg, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(obj, arg, order) \
    __atomic_op("amoand", obj, -arg, order)


/*
 * atomic_flag_test_and_set
 */

#define __atomic_flag_test_and_set_asm(obj, ASM_AQRL)               \
__extension__ ({                                                    \
    struct atomic_flag* __obj = (obj);                              \
    size_t __shift = (((unsigned long)__obj) & 3) << 3;             \
    uint32_t *__word = (uint32_t *)(((unsigned long)__obj) & ~3);   \
    uint32_t __mask = 1 << __shift;                                 \
    uint32_t __result;                                              \
    __asm__ volatile (                                              \
          "amoor.w" ASM_AQRL " %0, %2, %1\n"                        \
        : "=&r"(__result), "+A"(*__word)                            \
        : "r"(__mask)                                               \
        : "memory"                                                  \
    );                                                              \
    ((__result >> __shift) & 0xff);                                 \
})

#define __atomic_flag_test_and_set_relaxed(obj) \
    __atomic_flag_test_and_set_asm(obj, "")

#define __atomic_flag_test_and_set_acquire(obj) \
    __atomic_flag_test_and_set_asm(obj, ".aq")

#define __atomic_flag_test_and_set_release(obj) \
    __atomic_flag_test_and_set_asm(obj, ".rl")

#define __atomic_flag_test_and_set_acq_rel(obj) \
    __atomic_flag_test_and_set_asm(obj, ".aqrl")

#define __atomic_flag_test_and_set_seq_cst(obj) \
    __atomic_flag_test_and_set_asm(obj, ".aqrl")


#define __atomic_flag_test_and_set(obj, order)                      \
__extension__ ({                                                    \
    _Bool __result;                                                 \
    switch (order) {                                                \
    case __ATOMIC_ACQUIRE:                                          \
    case __ATOMIC_CONSUME: /* promote to acquire for now */         \
        __result = __atomic_flag_test_and_set_acquire(obj); break;  \
    case __ATOMIC_RELEASE:                                          \
        __result = __atomic_flag_test_and_set_release(obj); break;  \
    case __ATOMIC_ACQ_REL:                                          \
        __result = __atomic_flag_test_and_set_acq_rel(obj); break;  \
    case __ATOMIC_SEQ_CST:                                          \
        __result = __atomic_flag_test_and_set_seq_cst(obj); break;  \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __result = __atomic_flag_test_and_set_relaxed(obj); break;  \
    }                                                               \
    __result;                                                       \
})

#define atomic_flag_test_and_set_explicit(obj, order) \
    __atomic_flag_test_and_set(obj, order)
#define atomic_flag_test_and_set(obj, order) \
    __atomic_flag_test_and_set(obj, __ATOMIC_SEQ_CST)

/*
 * atomic_flag_clear
 */

#define __atomic_flag_clear_asm(obj, ASM_AQRL)                      \
__extension__ ({                                                    \
    struct atomic_flag* __obj = (obj);                              \
    size_t __shift = (((unsigned long)__obj) & 3) << 3;             \
    uint32_t *__word = (uint32_t *)(((unsigned long)__obj) & ~3);   \
    uint32_t __mask = ~(0xff << __shift);                           \
    uint32_t __result;                                              \
    __asm__ volatile (                                              \
          "amoand.w" ASM_AQRL " %0, %2, %1\n"                       \
        : "=&r"(__result), "+A"(*__word)                            \
        : "r"(__mask)                                               \
        : "memory"                                                  \
    );                                                              \
    ((__result >> __shift) & 0xff);                                 \
})

#define __atomic_flag_clear_relaxed(obj) \
    __atomic_flag_clear_asm(obj, "")

#define __atomic_flag_clear_acquire(obj) \
    __atomic_flag_clear_asm(obj, ".aq")

#define __atomic_flag_clear_release(obj) \
    __atomic_flag_clear_asm(obj, ".rl")

#define __atomic_flag_clear_acq_rel(obj) \
    __atomic_flag_clear_asm(obj, ".aqrl")

#define __atomic_flag_clear_seq_cst(obj) \
    __atomic_flag_clear_asm(obj, ".aqrl")


#define __atomic_flag_clear(obj, order)                             \
__extension__ ({                                                    \
    _Bool __result;                                                 \
    switch (order) {                                                \
    case __ATOMIC_ACQUIRE:                                          \
    case __ATOMIC_CONSUME: /* promote to acquire for now */         \
        __result = __atomic_flag_clear_acquire(obj); break;         \
    case __ATOMIC_RELEASE:                                          \
        __result = __atomic_flag_clear_release(obj); break;         \
    case __ATOMIC_ACQ_REL:                                          \
        __result = __atomic_flag_clear_acq_rel(obj); break;         \
    case __ATOMIC_SEQ_CST:                                          \
        __result = __atomic_flag_clear_seq_cst(obj); break;         \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __result = __atomic_flag_clear_relaxed(obj); break;         \
    }                                                               \
    __result;                                                       \
})

#define atomic_flag_clear_explicit(obj, order) \
    __atomic_flag_clear(obj, order)
#define atomic_flag_clear(obj, order) \
    __atomic_flag_clear(obj, __ATOMIC_SEQ_CST)

/*
 * atomic_thread_fence
 */

#define __atomic_thread_fence_asm(order)                            \
__extension__ ({                                                    \
    switch (order) {                                                \
    case __ATOMIC_ACQUIRE:                                          \
    case __ATOMIC_CONSUME: /* promote to acquire for now */         \
        __asm__ volatile ("fence r,rw" ::: "memory"); break;        \
    case __ATOMIC_RELEASE:                                          \
        __asm__ volatile ("fence rw,w" ::: "memory"); break;        \
    case __ATOMIC_ACQ_REL: /* should be fence.tso */                \
        __asm__ volatile ("fence rw,rw" ::: "memory"); break;       \
    case __ATOMIC_SEQ_CST:                                          \
        __asm__ volatile ("fence rw,rw" ::: "memory"); break;       \
    case __ATOMIC_RELAXED:                                          \
    default:                                                        \
        __asm__ volatile ("" ::: "memory"); break;                  \
    }                                                               \
})

#define atomic_thread_fence(order) \
    __atomic_thread_fence_asm(order)

/*
 * atomic_signal_fence
 */

#define atomic_signal_fence(order) \
    __asm__ volatile ("" ::: "memory")

#endif /* __riscv */

#ifdef __cplusplus
}
#endif
