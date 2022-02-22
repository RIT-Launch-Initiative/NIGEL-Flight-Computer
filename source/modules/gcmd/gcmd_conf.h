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

#define END_OF_GCMD_LIST {0, NULL}

// MAP FUNCTIONS TO CONTROL NUMBERS
static gcmd_entry_t gcmd_list[] = 
{
    {1, some_function},
    END_OF_GCMD_LIST
};

#endif
