#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>
#include "nuclei_demosoc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Read whole 64 bits value of mcycle counter
 * \details This function will read the whole 64 bits of MCYCLE register
 * \return  The whole 64 bits value of MCYCLE
 * \remarks It will work for both RV32 and RV64 to get full 64bits value of MCYCLE
 */
uint64_t __get_rv_cycle(void)
{
#if __RISCV_XLEN == 32
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
#elif __RISCV_XLEN == 64
    return (uint64_t)__read_csr(CSR_MCYCLE);
#else // TODO Need cover for XLEN=128 case in future
    return (uint64_t)__read_csr(CSR_MCYCLE);
#endif
}

/**
 * \brief   Read whole 64 bits value of machine instruction-retired counter
 * \details This function will read the whole 64 bits of MINSTRET register
 * \return  The whole 64 bits value of MINSTRET
 * \remarks It will work for both RV32 and RV64 to get full 64bits value of MINSTRET
 */
uint64_t __get_rv_instret(void)
{
#if __RISCV_XLEN == 32
    volatile uint32_t high0, low, high;
    uint64_t full;

    high0 = __read_csr(CSR_MINSTRETH);
    low = __read_csr(CSR_MINSTRET);
    high = __read_csr(CSR_MINSTRETH);
    if (high0 != high) {
        low = __read_csr(CSR_MINSTRET);
    }
    full = (((uint64_t)high) << 32) | low;
    return full;
#elif __RISCV_XLEN == 64
    return (uint64_t)__read_csr(CSR_MINSTRET);
#else // TODO Need cover for XLEN=128 case in future
    return (uint64_t)__read_csr(CSR_MINSTRET);
#endif
}

#ifdef __cplusplus
}
#endif
#endif /* _MAIN_H */
