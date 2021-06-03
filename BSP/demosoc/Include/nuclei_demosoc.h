// See LICENSE for license details.
#ifndef _NUCLEI_DEMOSOC_H
#define _NUCLEI_DEMOSOC_H

#include <intrinsics.h>
#include <stdint.h>
#include <stdio.h>

#include "riscv_encoding.h"
#include "demosoc_eclic.h"
#include "demosoc_systimer.h"
#include "demosoc_uart.h"
#include "demosoc_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#if __riscv_xlen == 32
  typedef uint32_t rv_csr_t;
#elif __riscv_xlen == 64
  typedef uint64_t rv_csr_t;
#else
  typedef uint32_t rv_csr_t;
#endif

#define read_csr                    __read_csr
#define set_csr                     __write_csr
#define write_csr                   __write_csr
#define clear_csr                   __clear_bits_csr

// IOF Settings for UART0 and UART1
#define IOF0_UART0_MASK             _AC(0x00030000, UL)
#define IOF_UART0_RX                (16u)
#define IOF_UART0_TX                (17u)
  
#define IOF0_UART1_MASK             _AC(0x03000000, UL)
#define IOF_UART1_RX                (24u)
#define IOF_UART1_TX                (25u)

// Peripherals memory map
#define DEMOSOC_PERIPH_BASE         (0x10000000UL)                          /*!< (Peripheral) Base Address */

#define GPIO_BASE                   (DEMOSOC_PERIPH_BASE + 0x12000)         /*!< (GPIO) Base Address */
#define UART0_BASE                  (DEMOSOC_PERIPH_BASE + 0x13000)         /*!< (UART0) Base Address */
#define ECLIC_BASE                  (0x0C000000UL)                          /*!< Set to ECLIC baseaddr of your device */
#define SYSTIMER_BASE               (0x02000000UL)                          /*!< Set to SysTimer baseaddr of your device */

/** register structures to access demosoc resources */
#define GPIO                        ((GPIO_TypeDef *) GPIO_BASE)
#define UART0                       ((UART_TypeDef *) UART0_BASE)
#define ECLIC                       ((CLIC_Type *) ECLIC_BASE)
#define SysTimer                    ((SysTimer_Type *) SYSTIMER_BASE)

/** Debug UART */
#define SOC_DEBUG_UART              UART0

#define RTC_FREQ                    32768
// The TIMER frequency is just the RTC frequency
#define SOC_TIMER_FREQ              RTC_FREQ
#ifndef SYSTEM_CLOCK
#define SYSTEM_CLOCK                (160000000UL)
#endif
  

#ifdef __cplusplus
}
#endif
#endif
