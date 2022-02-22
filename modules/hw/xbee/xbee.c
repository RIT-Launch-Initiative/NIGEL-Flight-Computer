/**
 * XBEE Radio Library
 *
 * @author Aaron Chan
 */

#include <stdlib.h>
#include "xbee.h"

xb_ret_t xb_transmit(uint8_t radius, void *payload) {
    xb_frame_t *frame = (xb_frame_t *) malloc(sizeof(xb_frame_t));

    if (frame == NULL) {
        return XB_ERR;
    }

    frame->start_delimiter = 0x7E;
    frame->length = 0x05;
    frame->frame_type = 0x10;
    frame->frame_id = 0x01;
    frame->dst_address_64 = 0x000000000000FFFF;
    frame->dst_address_16 = 0xFFFE;
    frame->radius = radius;
    frame->options = 0x80;
    frame->payload = (uint64_t *) payload;
    frame->checksum = 0xFF - (sizeof(frame) - sizeof(frame->length) - sizeof(frame->start_delimiter));

    _xb_write(uint8_t *buf, size_t len);

    return XB_SUCCESS;
}



