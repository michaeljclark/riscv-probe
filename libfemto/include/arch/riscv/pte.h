#pragma once

enum {
    PTE_SHIFT_V   = 0,
    PTE_SHIFT_R   = 1,
    PTE_SHIFT_W   = 2,
    PTE_SHIFT_X   = 3,
    PTE_SHIFT_U   = 4,
    PTE_SHIFT_G   = 5,
    PTE_SHIFT_A   = 6,
    PTE_SHIFT_D   = 7,
    PTE_SHIFT_SW1 = 8,
    PTE_SHIFT_SW2 = 9,
    PTE_V         = 1 << PTE_SHIFT_V,
    PTE_R         = 1 << PTE_SHIFT_R,
    PTE_W         = 1 << PTE_SHIFT_W,
    PTE_X         = 1 << PTE_SHIFT_X,
    PTE_U         = 1 << PTE_SHIFT_U,
    PTE_G         = 1 << PTE_SHIFT_G,
    PTE_A         = 1 << PTE_SHIFT_A,
    PTE_D         = 1 << PTE_SHIFT_D,
    PTE_SW1       = 1 << PTE_SHIFT_SW1,
    PTE_SW2       = 1 << PTE_SHIFT_SW2
};

enum {
    SV32_LEVELS = 2,
    SV32_LEVEL_BITS = 10,
    SV32_PTE_SIZE = 4
};

union sv32_va {
    uint32_t val;
    struct {
        uint32_t pg_off : 12;
        uint32_t vpn    : 20;
    } va;
};

union sv32_pa {
    uint64_t val;
    struct {
        uint64_t pg_off  : 12;
        uint64_t ppn     : 22;
        uint64_t rsrv    : 30;
    } pa;
};

union sv32_pte {
    uint32_t val;
    struct {
        uint32_t flags   : 10;
        uint32_t ppn     : 22;
    } pte;
};

enum {
    SV39_LEVELS = 3,
    SV39_LEVEL_BITS = 9,
    SV39_PTE_SIZE = 8
};

union sv39_va {
    uint64_t val;
    struct {
        uint64_t pg_off  : 12;
        uint64_t vpn     : 27;
        uint64_t rsrv    : 25;
    } va;
};

union sv39_pa {
    uint64_t val;
    struct {
        uint64_t pg_off  : 12;
        uint64_t ppn     : 44;
        uint64_t rsrv    : 8;
    } pa;
};

union sv39_pte {
    uint64_t val;
    struct {
        uint64_t flags   : 10;
        uint64_t ppn     : 44;
        uint64_t rsrv    : 10;
    } pte;
};

enum {
    SV48_LEVELS = 4,
    SV48_LEVEL_BITS = 9,
    SV48_PTE_SIZE = 8
};

union sv48_va {
    uint64_t val;
    struct {
        uint64_t pg_off  : 12;
        uint64_t vpn     : 36;
        uint64_t rsrv    : 16;
    } va;
};

union sv48_pa {
    uint64_t val;
    struct {
        uint64_t pg_off  : 12;
        uint64_t ppn     : 44;
        uint64_t rsrv    : 8;
    } pa;
};

union sv48_pte {
    uint64_t val;
    struct {
        uint64_t flags   : 10;
        uint64_t ppn     : 44;
        uint64_t rsrv    : 10;
    } pte;
};
