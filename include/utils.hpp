#ifndef __UTILS_HPP_INCLUDED__
#define __UTILS_HPP_INCLUDED__

#include <attributes.hpp>
#include <inttypes.hpp>
#include <kprintf.hpp>
#include <stdarg.h>

#define KB *1024
#define MB *1024 * 1024
#define GB *1024 * 1024 * 1024

INLINE static Uint64 alignUp(Uint64 value, Uint64 align) {
    return ((value + align - 1) / align) * align;
}

INLINE static Uint64 alignDown(Uint64 value, Uint64 align) {
    return (value / align) * align;
}

INLINE static void panic(const char* msg) {
    kprintf("\u001b[31m");
    kprintf(msg);
    while (1) {
        asm("pause");
    }
}

// Used for fast bitmap scanning. Source is taken from
// https://www.chessprogramming.org/BitScan#Bsf.2FBsr_x86-64_Timings
INLINE Uint8 bitScanForward(Uint64 x) {
    asm("bsfq %0, %0" : "=r"(x) : "0"(x));
    return (Uint8)x;
}

#define ALIGN_UP(x, align) (alignUp((Uint64)x, (Uint64)align))
#define ALIGN_DOWN(x, align) (alignUp((Uint64)x, (Uint64)align))

INLINE static void zeroPage(void* addr) {
    Uint64* p = (Uint64*)addr;
    for (Uint16 i = 0; i < 512; ++i) {
        p[i] = 0;
    }
}

#define UINT64_MAX 0xFFFFFFFFFFFFFFFF

#endif