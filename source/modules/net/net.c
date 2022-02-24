/*
*   Generic network functions
*   ntoh and hton functions assume system is little endian order (true for ARM)
*/
#include "net.h"
#include <stdlib.h>

// little endian to big endian

uint16_t hton16(uint16_t n) {
    uint8_t ret[sizeof(uint16_t)];

    for(size_t i = 0; i < sizeof(uint16_t); i++) {
        ret[i] = n;
        n >>= 8;
    }

    return *((uint16_t*)ret);
}

uint32_t hton32(uint32_t n) {
    uint8_t ret[sizeof(uint32_t)];

    for(size_t i = 0; i < sizeof(uint32_t); i++) {
        ret[i] = n;
        n >>= 8;
    }

    return *((uint32_t*)ret);
}

uint64_t hton64(uint64_t n) {
    uint8_t ret[sizeof(uint64_t)];

    for(size_t i = 0; i < sizeof(uint64_t); i++) {
        ret[i] = n;
        n >>= 8;
    }

    return *((uint64_t*)ret);
}

// big endian to little endian

uint16_t ntoh16(uint16_t n) {
    uint8_t ret[sizeof(uint16_t)];

    for(size_t i = 0; i < sizeof(uint16_t); i++) {
        ret[sizeof(uint16_t) - i - 1] = n;
        n >>= 8;
    }

    return *((uint16_t*)ret);
}

uint32_t ntoh32(uint32_t n) {
    uint8_t ret[sizeof(uint32_t)];

    for(size_t i = 0; i < sizeof(uint32_t); i++) {
        ret[sizeof(uint32_t) - i - 1] = n;
        n >>= 8;
    }

    return *((uint32_t*)ret);
}

uint64_t ntoh64(uint64_t n) {
    uint8_t ret[sizeof(uint64_t)];

    for(size_t i = 0; i < sizeof(uint64_t); i++) {
        ret[sizeof(uint64_t) - i - 1] = n;
        n >>= 8;
    }

    return *((uint64_t*)ret);
}
