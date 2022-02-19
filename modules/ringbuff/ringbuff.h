#ifndef RINGBUFF_H
#define RINGBUFF_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int head; // first byte occupied at beginning (aka first byte we can read from)
    int tail; // first byte free at end (aka first byte we can write to)
    uint8_t* ptr; // ptr to beginning of buffer
    int max; // max size
    uint8_t overwrite_enable; // whether or not the head of the ringbuffer can be overwritten
} ringbuff_t;

// need to pass in a buffer of size 'size' for the ring buffer to use
// assumes buffer and ringbuffer struct are preallocated
// sets head and tail correctly
// if 'overwrite_enable' is non-zero, the head of the buffer can be overwritten when data is copied in
// if this flag is 0, writes that would overfill the buffer return 0 and no data is copied
void rbuff_init(ringbuff_t* rb, uint8_t* buff, size_t size, uint8_t overwrite_enable);

// copy len bytes from buff into rb
// returns number of bytes copied
size_t rbuff_memcpyin(ringbuff_t* rb, uint8_t* buff, size_t len);

// copy len bytes from rb into buff
// returns number of bytes copied
size_t rbuff_memcpyout(uint8_t* buff, ringbuff_t* rb, size_t len);

#endif
