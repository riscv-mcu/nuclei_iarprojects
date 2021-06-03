#include <stdio.h>
#include <stdlib.h>
#include <intrinsics.h>
#include "coremark.h"

#if VALIDATION_RUN
volatile ee_s32 seed1_volatile = 0x3415;
volatile ee_s32 seed2_volatile = 0x3415;
volatile ee_s32 seed3_volatile = 0x66;
#endif

#if PERFORMANCE_RUN
volatile ee_s32 seed1_volatile = 0x0;
volatile ee_s32 seed2_volatile = 0x0;
volatile ee_s32 seed3_volatile = 0x66;
#endif

#if PROFILE_RUN
volatile ee_s32 seed1_volatile = 0x8;
volatile ee_s32 seed2_volatile = 0x8;
volatile ee_s32 seed3_volatile = 0x8;
#endif

volatile ee_s32 seed4_volatile = ITERATIONS;
volatile ee_s32 seed5_volatile = 0;

static CORE_TICKS t0, t1;

static inline uint64_t __get_rv_cycle(void)
{
#if __riscv_xlen == 32
    volatile uint32_t high0, low, high;
    uint64_t full;

    high0 = __read_csr(CSR_MCYCLEH);
    low = __read_csr(CSR_MCYCLE);
    high = __read_csr(CSR_MCYCLEH);
    if (high0 != high) {
        low = __read_csr(CSR_MCYCLE);
    }
    full = (((uint64_t)high) << 32) | low;
    return full;
#elif __riscv_xlen == 64
    return (uint64_t)__read_csr(CSR_MCYCLE);
#else // TODO Need cover for XLEN=128 case in future
    return (uint64_t)__read_csr(CSR_MCYCLE);
#endif
}

void start_time(void)
{
    t0 = __get_rv_cycle();
}

void stop_time(void)
{
    t1 = __get_rv_cycle();
}

CORE_TICKS get_time(void)
{
    return t1 - t0;
}

extern uint32_t SystemCoreClock;

secs_ret time_in_secs(CORE_TICKS ticks)
{
    // scale timer down to avoid uint64_t -> double conversion in RV32
    int scale = 256;
    uint64_t delta = ticks / scale;
    uint64_t freq = SystemCoreClock / scale;
    return delta / (double)freq;
}
