/*
*   UDP implementation
*
*   author: Will Merges @ RIT Launch Initiative
*/
#ifndef UDP_H
#define UDP_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t len;
    uint16_t checksum;
} udp_header_t;

// NOTE: checksum calculations should be run on the header AND payload
//       assumes the 'checksum' field in the header is already zeroed
uint16_t udp_calculate_checksum(uint8_t* data, size_t len);

#endif
