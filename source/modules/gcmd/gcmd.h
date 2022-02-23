/*
*   Parse ground commands
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef GCMD_H
#define GCMD_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint32_t seq_num;
    uint16_t control;
    uint16_t state;
} gcmd_t;

// init this module
// return -1 on failure, 1 otherwise
int gcmd_init();

// parse a command from an input source
// return -1 on failure, 1 otherwise
int gcmd_parse(uint8_t* buff, size_t len);

#endif
