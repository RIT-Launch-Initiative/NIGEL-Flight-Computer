/*
*   Flight Termination System source
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef FTS_H
#define FTS_H

#include <stdint.h>

// state constants
#define FTS_DISARMED 0  // disarmed, ignore terminate commands
#define FTS_ARMED    1  // armed, ready for terminate command
#define FTS_TERMN    99 // terminate vehicle

// set state of the FTS system
// NOTE: this function is primarily used as a layer to parse ground commands
void fts_set_state(uint16_t state, void*);

// arm the FTS
void fts_arm();

// disarm the FTS
void fts_disarm();

// terminate the vehicle
// NOTE: ignores termination command if not armed
void fts_termn();

#endif
