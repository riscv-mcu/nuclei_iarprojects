#include "nuclei_demosoc.h"

#if defined(DEBUG_SEMIHOST) && DEBUG_SEMIHOST == 0
int putchar(int ch)
{
    if (ch == '\n') {
        uart_write(SOC_DEBUG_UART, '\r');
    }
    uart_write(SOC_DEBUG_UART, ch);

    return ch;
}
#endif