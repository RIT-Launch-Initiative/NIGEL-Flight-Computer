/*
*   Flight Termination System source
*
*   Will Merges @ RIT Launch Initiative
*/
#include "fts.h"
#include <stdint.h>

static uint8_t armed = 0;

void fts_set_state(uint16_t state, void* unused_src_addr) {
    switch(state) {
        case FTS_DISARMED:
            fts_disarm();
            break;
        case FTS_ARMED:
            fts_arm();
            break;
        case FTS_TERMN:
            fts_termn();
            break;
    }
}

void fts_arm() {
    armed = 1;
}

void fts_disarm() {
    armed = 0;
}

void fts_termn() {
    if(!armed) {
        return;
    }

    // TODO boom
}
