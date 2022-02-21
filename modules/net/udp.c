#include "udp.h"

uint16_t udp_calculate_checksum(uint8_t* data, size_t len) {
    uint16_t c = 0;
	for(; len>1; len -= 2) {
        c += *data++;
    }

    if(len == 1) {
        c += *(uint16_t*)data;
    }
   
    return c;
}

// assumes system is little endian (default for ARM)
uint16_t htons(uint16_t n) {
    uint16_t ret = n >> 8; // MSB to LSB
    ret |= n << 8; // LSB to MSB

    return ret;
}
