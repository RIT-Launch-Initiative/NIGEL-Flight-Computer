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

#include "fts.h"

// -----------------------------------------


// MAP FUNCTIONS TO CONTROL NUMBERS

#define NUM_GCMDS 2
static gcmd_entry_t gcmd_list[NUM_GCMDS] =
{
    {900, NULL}, // TODO link these
    {99, &fts_set_state}
};

#endif
