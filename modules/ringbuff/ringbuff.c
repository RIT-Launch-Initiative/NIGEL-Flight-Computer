#include <stdint.h>
#include <stdlib.h>
#include "ringbuff.h"

void rbuff_init(ringbuff_t* rb, uint8_t* buff, size_t size, uint8_t overwrite_enable) {
    rb->head = 0;
    rb->tail = 0;
    rb->ptr = buff;
    rb->max = size;
    rb->overwrite_enable = overwrite_enable;
}


size_t rbuff_memcpyin(ringbuff_t* rb, uint8_t* buff, size_t len) {
    // if we will overwrite head, move it to one after what we will write
    if((len + rb->tail) % rb->max > rb->head) {
        if(rb->overwrite_enable) {
            rb->head = (len + rb->tail) % rb->max;
        } else {
            return 0;
        }
    }

    size_t i = 0;
    while(i < len) {
        rb->ptr[rb->tail] = buff[i];
        i++;
        rb->tail = (rb->tail + 1) % rb->max;
    }

    return i;
}

size_t rbuff_memcpyout(uint8_t* buff, ringbuff_t* rb, size_t len) {
    size_t i = 0;
    while(i < len) {
        buff[i] = rb->ptr[rb->head];
        i++;
        rb->head = (rb->head + 1) % rb->max;
        if(rb->head == rb->tail) {
            return i;
        }
    }
    return i;
}
