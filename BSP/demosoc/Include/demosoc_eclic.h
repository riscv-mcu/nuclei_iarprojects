// See LICENSE for license details.
#ifndef _DEMOSOC_ECLIC_H
#define _DEMOSOC_ECLIC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief  Union type to access CLICFG configure register.
 */
typedef union
{
    struct {
        uint8_t _reserved0:1;                   /*!< bit:     0   Overflow condition code flag */
        uint8_t nlbits:4;                       /*!< bit:     29  Carry condition code flag */
        uint8_t _reserved1:2;                   /*!< bit:     30  Zero condition code flag */
        uint8_t _reserved2:1;                   /*!< bit:     31  Negative condition code flag */
    } b;                                        /*!< Structure used for bit  access */
    uint8_t w;                                  /*!< Type      used for byte access */
} CLICCFG_Type;

/**
 * \brief  Union type to access CLICINFO information register.
 */
typedef union {
    struct {
        uint32_t numint:13;                     /*!< bit:  0..12   number of maximum interrupt inputs supported */
        uint32_t version:8;                     /*!< bit:  13..20  20:17 for architecture version,16:13 for implementation version */
        uint32_t intctlbits:4;                  /*!< bit:  21..24  specifies how many hardware bits are actually implemented in the clicintctl registers */
        uint32_t _reserved0:7;                  /*!< bit:  25..31  Reserved */
    } b;                                        /*!< Structure used for bit  access */
    uint32_t w;                                 /*!< Type      used for word access */
} CLICINFO_Type;

/**
 * \brief Access to the structure of a vector interrupt controller.
 */
typedef struct {
    volatile uint8_t  INTIP;                       /*!< Offset: 0x000 (R/W)  Interrupt set pending register */
    volatile uint8_t  INTIE;                       /*!< Offset: 0x001 (R/W)  Interrupt set enable register */
    volatile uint8_t  INTATTR;                     /*!< Offset: 0x002 (R/W)  Interrupt set attributes register */
    volatile uint8_t  INTCTRL;                     /*!< Offset: 0x003 (R/W)  Interrupt configure register */
} CLIC_CTRL_Type;

typedef struct {
    volatile uint8_t   CFG;                        /*!< Offset: 0x000 (R/W)  CLIC configuration register */
    volatile uint8_t RESERVED0[3];
    volatile uint32_t  INFO;                        /*!< Offset: 0x004 (R/ )  CLIC information register */
    volatile uint8_t RESERVED1[3];
    volatile uint8_t  MTH;                         /*!< Offset: 0x00B (R/W)  CLIC machine mode threshold register */
    volatile uint32_t RESERVED2[0x3FD];
    volatile CLIC_CTRL_Type CTRL[4096];                  /*!< Offset: 0x1000 (R/W) CLIC register structure for INTIP, INTIE, INTATTR, INTCTL */
} CLIC_Type;

#ifdef __cplusplus
}
#endif
#endif /* _DEMOSOC_ECLIC_H */
