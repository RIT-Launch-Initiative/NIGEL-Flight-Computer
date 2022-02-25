/*
*   Spinlock functions
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <stdint.h>

// 48 MHz
#define CPU_CLOCK_SPEED 48000000 // Hz

// spin for 'ms' milliseconds
void spinlock(uint32_t ms);

#endif
