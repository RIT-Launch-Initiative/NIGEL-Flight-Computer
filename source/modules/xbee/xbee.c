/**
 * XBEE Radio Library
 *
 * @author Aaron Chan
 */

#include <stdint.h>
#include <stdlib.h>
#include "xbee.h"

typedef struct {
    uint8_t start_delimiter;
    uint16_t length;
    uint8_t frame_type;
    uint64_t dst_address_64;
    uint16_t reserved;
    uint8_t radius;
    uint8_t options;
} xb_tx_frame_t;

typedef struct {
    uint8_t start_delimiter;
    uint16_t length;
    uint8_t frame_type;
    uint64_t src_address_64;
    uint16_t src_address_16;
    uint8_t options;
    uint64_t received;
    uint8_t checksum;
} xb_rx_frame_t;

static uint8_t tx_buff[1024];

xb_ret_t xb_tx(uint8_t *data, size_t len) {
    xb_tx_frame_t *frame = (xb_tx_frame_t *) tx_buff;

    if (frame == NULL) {
        return XB_ERR;
    }

    frame->start_delimiter = 0x7E;
    frame->length = 0x05;
    frame->frame_type = 0x10;
    frame->dst_address_64 = 0x000000000000FFFF;
    frame->reserved = 0xFFFE;
    frame->radius = 0;
    frame->options = 0x80;

    uint8_t check = 0;

    for (int i = 3; i < frame->length + sizeof(xb_tx_frame_t); i++) {
        check += data[i];
    }

    return XB_OK;
}

void xb_attach_rx_callback(void (*rx)(uint8_t *buff, size_t len)) {


}


void xb_raw_recv(uint8_t *buff, size_t len) {
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

void xb_set_dst(uint64_t addr) {

}

xb_ret_t xb_cmd_dio(xbee_dio_t dio, xbee_dio_output_t output) {

}


void xb_init(int (*write)(uint8_t *buf, size_t len)) {
//    _xb_write = write;

    // TODO: More stuff
}





