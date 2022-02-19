#ifndef COMMON_H
#define COMMON_H

typedef enum {
    RET_ERROR,
    RET_BLOCKED,
    RET_OK
} RetType;

// enable / disable interrupt masks on the CPU
#define enable_irq __ASM volatile ("cpsie i" : : : "memory");
#define disable_irq __ASM volatile ("cpsid i" : : : "memory");

#endif
