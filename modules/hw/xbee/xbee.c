/**
 * XBEE Radio Library
 *
 * @author Aaron Chan
 */

#include <stdint.h>
#include <stdlib.h>
#include "xbee.h"

xb_ret_t xb_transmit(uint8_t radius, void *payload, int (*write)(uint8_t *buf, size_t len)) {
    xb_tx_frame_t *frame = (xb_tx_frame_t *) malloc(sizeof(xb_tx_frame_t));

    if (frame == NULL) {
        return XB_ERR;
    }

    frame->start_delimiter = 0x7E;
    frame->length = 0x05;
    frame->frame_type = 0x10;
    frame->dst_address_64 = 0x000000000000FFFF;
    frame->dst_address_16 = 0xFFFE;
    frame->radius = radius; // ?
    frame->options = 0x80;
    frame->payload = (uint64_t) payload; // ?
    frame->checksum = 0xFF - (sizeof(frame) - sizeof(frame->length) - sizeof(frame->start_delimiter)); // ?

//    *_xb_write();

    return XB_OK;
}

xb_ret_t xb_receive() {
    xb_rx_frame_t *frame = (xb_rx_frame_t *) malloc(sizeof(xb_rx_frame_t));

    if (frame == NULL) {
        return XB_ERR;
    }

    // TODO: Figure out what options need to be set to
    frame->start_delimiter = 0x90;
    frame->length = 0x05;
    frame->frame_type = 0x90;
    frame->src_address_64 = 0x000000000000FFFF; // ?
    frame->src_address_16 = 0xFFFE; // ?
    frame->options = 0x02; // ?
    frame->received = 0x00; // ?
    frame->checksum = 0xFF - (sizeof(frame) - sizeof(frame->length) - sizeof(frame->start_delimiter));

    return XB_OK;
}


void xb_init(int (*write)(uint8_t *buf, size_t len)) {
//    _xb_write = write;

    // TODO: More stuff
}





