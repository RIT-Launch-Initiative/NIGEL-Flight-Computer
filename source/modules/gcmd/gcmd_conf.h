/*
*   Ground command module configuration
*/
#ifndef GCMD_CONF_H
#define GCMD_CONF_H

#include <stdint.h>

typedef struct {
    uint16_t control;
    void (*func) (uint16_t state, void* addr_info);
} gcmd_entry_t;

// INSERT INCLUDES FOR MAPPED FUNCTIONS HERE
// -----------------------------------------

#include "fts.h"
#include "comm.h"

// -----------------------------------------


// MAP FUNCTIONS TO CONTROL NUMBERS

#define NUM_GCMDS 2
static gcmd_entry_t gcmd_list[NUM_GCMDS] =
{
    {99, &fts_set_state},
    {0, &comm_heartbeat}
};

#endif
