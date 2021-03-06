#include <stdint.h>
#include <stdlib.h>
#include "ringbuff.h"

void rb_init(ringbuff_t* rb, uint8_t* buff, size_t size, uint8_t overwrite_enable) {
    rb->head = 0;
    rb->tail = 0;
    rb->ptr = buff;
    rb->max = size;
    rb->len = 0;
    rb->overwrite_enable = overwrite_enable;
}


size_t rb_memcpyin(ringbuff_t* rb, uint8_t* buff, size_t len) {
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

    rb->len += i;
    return i;
}

size_t rb_memcpyout(uint8_t* buff, ringbuff_t* rb, size_t len) {
    size_t i = 0;
    while(i < len) {
        buff[i] = rb->ptr[rb->head];
        i++;
        rb->head = (rb->head + 1) % rb->max;
        if(rb->head == rb->tail) {
            rb->len -= i;
            return i;
        }
    }

    rb->len -= i;
    return i;
}
