#include <stdlib.h>
#include "nuclei_demosoc.h"

extern __weak void   eclic_msip_handler();
extern __weak void   eclic_mtip_handler();
extern __weak void   eclic_irq19_handler();
extern __weak void   eclic_irq20_handler();
extern __weak void   eclic_irq21_handler();
extern __weak void   eclic_irq22_handler();
extern __weak void   eclic_irq23_handler();
extern __weak void   eclic_irq24_handler();
extern __weak void   eclic_irq25_handler();
extern __weak void   eclic_irq26_handler();
extern __weak void   eclic_irq27_handler();
extern __weak void   eclic_irq28_handler();
extern __weak void   eclic_irq29_handler();
extern __weak void   eclic_irq30_handler();
extern __weak void   eclic_irq31_handler();
extern __weak void   eclic_irq32_handler();
extern __weak void   eclic_irq33_handler();
extern __weak void   eclic_irq34_handler();
extern __weak void   eclic_irq35_handler();
extern __weak void   eclic_irq36_handler();
extern __weak void   eclic_irq37_handler();
extern __weak void   eclic_irq38_handler();
extern __weak void   eclic_irq39_handler();
extern __weak void   eclic_irq40_handler();
extern __weak void   eclic_irq41_handler();
extern __weak void   eclic_irq42_handler();
extern __weak void   eclic_irq43_handler();
extern __weak void   eclic_irq44_handler();
extern __weak void   eclic_irq45_handler();
extern __weak void   eclic_irq46_handler();
extern __weak void   eclic_irq47_handler();
extern __weak void   eclic_irq48_handler();
extern __weak void   eclic_irq49_handler();
extern __weak void   eclic_irq50_handler();
extern __weak void   eclic_irq51_handler();

typedef void(*__fp)();

#pragma data_alignment = 256
const __fp gd_vector_base[96] = {
    0,
    0,
    0,
    eclic_msip_handler,
    0,
    0,
    0,
    eclic_mtip_handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    eclic_irq19_handler,
    eclic_irq20_handler,
    eclic_irq21_handler,
    eclic_irq22_handler,
    eclic_irq23_handler,
    eclic_irq24_handler,
    eclic_irq25_handler,
    eclic_irq26_handler,
    eclic_irq27_handler,
    eclic_irq28_handler,
    eclic_irq29_handler,
    eclic_irq30_handler,
    eclic_irq31_handler,
    eclic_irq32_handler,
    eclic_irq33_handler,
    eclic_irq34_handler,
    eclic_irq35_handler,
    eclic_irq36_handler,
    eclic_irq37_handler,
    eclic_irq38_handler,
    eclic_irq39_handler,
    eclic_irq40_handler,
    eclic_irq41_handler,
    eclic_irq42_handler,
    eclic_irq43_handler,
    eclic_irq44_handler,
    eclic_irq45_handler,
    eclic_irq46_handler,
    eclic_irq47_handler,
    eclic_irq48_handler,
    eclic_irq49_handler,
    eclic_irq50_handler,
    eclic_irq51_handler,
    0
};

extern unsigned int __minterrupt_clic_base;
extern __interrupt __machine void __minterrupt_single(void);

__interrupt __machine void __default_minterrupt_handler(void);

__interrupt __machine void __default_minterrupt_handler(void)
{
    abort();
}

extern uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp);

uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp)
{
    __fp fp;
    mcause &= 0xFFF;
    fp = gd_vector_base[mcause];
    if (fp) {
        fp();
    }
    return 0;
}

__interrupt __preemptive void trap_entry()
{
    uintptr_t mcause = __read_csr(_CSR_MCAUSE);
    handle_trap(mcause, 0);
}

__interrupt __preemptive  void irq_entry()
{
    uint32_t mcause = read_csr(_CSR_MCAUSE);
    uint32_t mepc = read_csr(_CSR_MEPC);
    uint32_t msubm = read_csr(CSR_MSUBM);
    write_csr(CSR_MSTATUS, MSTATUS_MIE);

    handle_trap(mcause, 0);

    clear_csr(CSR_MSTATUS, MSTATUS_MIE);
    write_csr(CSR_MSUBM, msubm);
    write_csr(_CSR_MEPC, mepc);
    write_csr(_CSR_MCAUSE, mcause);
}

extern void _premain_init(void);

int __low_level_init()
{
    __disable_interrupt();

    /* Set the the NMI base to share with mtvec by setting CSR_MMISC_CTL */
    /* li t0, 0x200           */
    /* csrs CSR_MMISC_CTL, t0 */
    __set_bits_csr(/*CSR_MMISC_CTL*/ 0x7D0, 0x200);

    /* Initialize the mtvt */
    /* la t0, vector_base      */
    /* csrw CSR_MTVT, t0       */
    __write_csr(_CSR_MTVT, ((unsigned int)&gd_vector_base));
    /* Initialize the mtvt2 and enable it */
    /* la t0, irq_entry
    csrw CSR_MTVT2, t0
    csrs CSR_MTVT2, 0x1
    */
    __write_csr(/*_CSR_MTVT2*/ 0x7EC, 0x1 | ((unsigned int)&irq_entry));

    /* Initialize the CSR MTVEC for the Trap ane NMI base addr*/
    /* la t0, trap_entry
    csrw CSR_MTVEC, t0
    */
    __write_csr(_CSR_MTVEC, 0x03 | ((unsigned int)&trap_entry));

    /* Enable mycycle_minstret */
    __clear_bits_csr(/*CSR_MCOUNTINHIBIT*/ 0x320, 0x5);

    /* Get CPU frequency and initialize uart for print */
    _premain_init();

    return 1;
}