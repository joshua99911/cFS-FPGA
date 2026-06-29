/*******************************************************************************
**
** File: fpga_ctrl_kv260_platform.h
**
** Purpose:
**   KV260/Kria platform defaults for the FPGA Ctrl app.  Mission builds can
**   override any of these values from their mission platform configuration or
**   compiler definitions if the Vivado address map differs.
**
*******************************************************************************/

#ifndef FPGA_CTRL_KV260_PLATFORM_H
#define FPGA_CTRL_KV260_PLATFORM_H

#include <stddef.h>

#include "cfe.h"

#ifndef FPGA_CTRL_PLATFORM_NAME
#define FPGA_CTRL_PLATFORM_NAME "kv260"
#endif

/*
 * The defaults below match the example KV260 address map documented in
 * docs/kv260.md.  If your XSA uses different AXI-Lite base addresses, override
 * these values instead of editing the app logic.
 */
#ifndef FPGA_CTRL_MMIO_MAP_RANGE
#define FPGA_CTRL_MMIO_MAP_RANGE 0x00010000u
#endif

#ifndef FPGA_CTRL_AES_CONTROL_BASE
#define FPGA_CTRL_AES_CONTROL_BASE 0xA0000000u
#endif

#ifndef FPGA_CTRL_AES_INPUT_BASE
#define FPGA_CTRL_AES_INPUT_BASE 0xA0010000u
#endif

#ifndef FPGA_CTRL_AES_OUTPUT_BASE
#define FPGA_CTRL_AES_OUTPUT_BASE 0xA0020000u
#endif

#ifndef FPGA_CTRL_BUTTON_GPIO_BASE
#define FPGA_CTRL_BUTTON_GPIO_BASE 0xA0030000u
#endif

#ifndef FPGA_CTRL_SWITCH_GPIO_BASE
#define FPGA_CTRL_SWITCH_GPIO_BASE 0xA0040000u
#endif

#ifndef FPGA_CTRL_AES_KEY_OFFSET
#define FPGA_CTRL_AES_KEY_OFFSET 0x20u
#endif

#ifndef FPGA_CTRL_AES_PLAINTEXT_OFFSET
#define FPGA_CTRL_AES_PLAINTEXT_OFFSET 0x10u
#endif

#ifndef FPGA_CTRL_AES_CIPHERTEXT_OFFSET
#define FPGA_CTRL_AES_CIPHERTEXT_OFFSET 0x10u
#endif

#ifndef FPGA_CTRL_AES_AP_START_MASK
#define FPGA_CTRL_AES_AP_START_MASK 0x01u
#endif

#ifndef FPGA_CTRL_AES_AP_DONE_MASK
#define FPGA_CTRL_AES_AP_DONE_MASK 0x02u
#endif

#ifndef FPGA_CTRL_AES_TIMEOUT_MS
#define FPGA_CTRL_AES_TIMEOUT_MS 5000u
#endif

#ifndef FPGA_CTRL_AXI_GPIO_GIER_OFFSET
#define FPGA_CTRL_AXI_GPIO_GIER_OFFSET 0x11cu
#endif

#ifndef FPGA_CTRL_AXI_GPIO_ISR_OFFSET
#define FPGA_CTRL_AXI_GPIO_ISR_OFFSET 0x120u
#endif

#ifndef FPGA_CTRL_AXI_GPIO_IER_OFFSET
#define FPGA_CTRL_AXI_GPIO_IER_OFFSET 0x128u
#endif

#ifndef FPGA_CTRL_AXI_GPIO_GIER_ENABLE_MASK
#define FPGA_CTRL_AXI_GPIO_GIER_ENABLE_MASK 0x80000000u
#endif

#ifndef FPGA_CTRL_AXI_GPIO_IER_CH1_ENABLE_MASK
#define FPGA_CTRL_AXI_GPIO_IER_CH1_ENABLE_MASK 0x00000001u
#endif

#ifndef FPGA_CTRL_AXI_GPIO_ISR_CH1_MASK
#define FPGA_CTRL_AXI_GPIO_ISR_CH1_MASK 0x00000001u
#endif

/* Match this string to the UIO node name exposed by the KV260 device-tree overlay. */
#ifndef FPGA_CTRL_UIO_NAME
#define FPGA_CTRL_UIO_NAME "fpga_ctrl_button_irq"
#endif

/* Fallback only.  The runtime first searches /sys/class/uio by FPGA_CTRL_UIO_NAME. */
#ifndef FPGA_CTRL_UIO_DEVICE
#define FPGA_CTRL_UIO_DEVICE "/dev/uio0"
#endif

/* Script used by the reprogram command.  See scripts/program-fpga-kv260.sh. */
#ifndef FPGA_CTRL_PROGRAM_FPGA
#define FPGA_CTRL_PROGRAM_FPGA "/usr/local/bin/program-fpga-kv260.sh"
#endif

#ifndef FPGA_CTRL_STATUS_PL_TIMEOUT
#define FPGA_CTRL_STATUS_PL_TIMEOUT (-1001)
#endif

#ifndef FPGA_CTRL_STATUS_UIO_NOT_FOUND
#define FPGA_CTRL_STATUS_UIO_NOT_FOUND (-1002)
#endif

#ifndef FPGA_CTRL_STATUS_PROGRAM_FPGA_FAILED
#define FPGA_CTRL_STATUS_PROGRAM_FPGA_FAILED (-1003)
#endif

static inline uint8 FPGA_CTRL_MmioRead8(void const volatile *addr)
{
    return *(uint8 const volatile *)addr;
}

static inline uint32 FPGA_CTRL_MmioRead32(void const volatile *addr)
{
    return *(uint32 const volatile *)addr;
}

static inline void FPGA_CTRL_MmioWrite32(void volatile *addr, uint32 value)
{
    *(uint32 volatile *)addr = value;
}

static inline void FPGA_CTRL_MmioWriteBytes(void volatile *dst, void const *src, size_t len)
{
    uint8 volatile *const      dst8 = (uint8 volatile *)dst;
    uint8 const *const         src8 = (uint8 const *)src;

    for (size_t i = 0; i < len; ++i)
    {
        dst8[i] = src8[i];
    }
}

static inline void FPGA_CTRL_MmioReadBytes(void *dst, void const volatile *src, size_t len)
{
    uint8 *const               dst8 = (uint8 *)dst;
    uint8 const volatile *const src8 = (uint8 const volatile *)src;

    for (size_t i = 0; i < len; ++i)
    {
        dst8[i] = src8[i];
    }
}

#endif /* FPGA_CTRL_KV260_PLATFORM_H */
