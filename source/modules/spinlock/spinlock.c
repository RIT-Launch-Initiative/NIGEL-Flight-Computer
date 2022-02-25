#include "spinlock.h"

void spinlock(uint32_t ms) {
    uint64_t ticks = ms * CPU_CLOCK_SPEED / 1000;

    for(uint64_t i = 0; i < ticks; i++) { };

    return;
}
