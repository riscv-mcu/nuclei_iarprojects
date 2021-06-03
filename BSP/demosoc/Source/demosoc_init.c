#include "nuclei_demosoc.h"

volatile uint32_t SystemCoreClock = SYSTEM_CLOCK;

static uint32_t get_timer_freq()
{
    return SOC_TIMER_FREQ;
}

uint32_t measure_cpu_freq(uint32_t n)
{
    volatile uint32_t start_mcycle, delta_mcycle;
    volatile uint32_t start_mtime, delta_mtime;
    volatile uint32_t mtime_freq = get_timer_freq();

    // Don't start measuruing until we see an mtime tick
    volatile uint32_t tmp = (uint32_t)SysTimer->MTIMER;
    do {
        start_mtime = (uint32_t)SysTimer->MTIMER;
        start_mcycle = __read_csr(CSR_MCYCLE);
    } while (start_mtime == tmp);

    do {
        delta_mtime = (uint32_t)SysTimer->MTIMER - start_mtime;
        delta_mcycle = __read_csr(CSR_MCYCLE) - start_mcycle;
    } while (delta_mtime < n);

    mtime_freq = ((delta_mcycle / delta_mtime) * mtime_freq)
           + (((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime);
    return mtime_freq;
}

uint32_t get_cpu_freq(void)
{
    uint32_t cpu_freq;

    // warm up
    measure_cpu_freq(1);
    // measure for real
    cpu_freq = measure_cpu_freq(100);

    return cpu_freq;
}

/** Banner Print for Nuclei Demosoc */
void SystemBannerPrint(void)
{
    printf("Nuclei Demosoc IAR Project Build Time: %s, %s\r\n", __DATE__, __TIME__);
    printf("CPU Frequency %lu Hz\r\n", SystemCoreClock);
}

/**
 * \brief early init function before main
 * \details
 * This function is executed right before main function.
 */
void _premain_init(void)
{
    SystemCoreClock = get_cpu_freq();
    gpio_iof_config(GPIO, IOF0_UART0_MASK, IOF_SEL_0);
    uart_init(SOC_DEBUG_UART, 115200);
    /* Display banner after UART initialized */
    SystemBannerPrint();
}
