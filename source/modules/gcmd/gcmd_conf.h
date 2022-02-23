/*
*   Ground command module configuration
*/
#ifndef GCMD_CONF_H
#define GCMD_CONF_H

#include <stdint.h>

typedef struct {
    uint16_t control;
    void (*func) (uint16_t state);
} gcmd_entry_t;

// INSERT INCLUDES FOR MAPPED FUNCTIONS HERE
// -----------------------------------------

// -----------------------------------------


// MAP FUNCTIONS TO CONTROL NUMBERS

#define NUM_GCMDS 1
static gcmd_entry_t gcmd_list[NUM_GCMDS] =
{
    {900, NULL} // TODO link these
};

#endif
