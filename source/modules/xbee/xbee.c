/**
 * XBEE Radio Library
 *
 * @author Aaron Chan
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
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
    uint16_t reserved;
} xb_rx_frame_t;

static uint8_t tx_buff[1024];
static uint8_t rx_buff[1024];

xb_ret_t xb_tx(uint8_t *data, size_t len) {
    xb_tx_frame_t *frame = (xb_tx_frame_t *) tx_buff;

    frame->start_delimiter = 0x7E;
    frame->length = len;
    frame->frame_type = 0x10;
    frame->dst_address_64 = 0x000000000000FFFF;
    frame->reserved = 0xFFFE;
    frame->radius = 0;
    frame->options = 0x80;


    memcpy(tx_buff + sizeof(xb_tx_frame_t), data, len);

    uint8_t check = 0;
    for (int i = 3; i < frame->length + sizeof(xb_tx_frame_t); i++) {
        check += tx_buff[i];
    }

    check = 0xff - check;
    memcpy(tx_buff + frame->length + sizeof(xb_tx_frame_t), &check, 1);

    return XB_OK;
}

void xb_attach_rx_callback(void (*rx)(uint8_t *buff, size_t len)) {


}


void xb_raw_recv(uint8_t *buff, size_t len) {
    xb_rx_frame_t *frame = (xb_rx_frame_t *) rx_buff;

    frame->start_delimiter = 0x7E;
    frame->length = len;
    frame->frame_type = 0x90;
    frame->src_address_64 = 0x000000000000FFFF;
    frame->reserved = 0xFFFE;


}

void xb_set_dst(uint64_t addr) {
    xb_tx_frame_t *frame = (xb_tx_frame_t *) tx_buff;
    frame->dst_address_64 = addr;
}

xb_ret_t xb_cmd_dio(xbee_dio_t dio, xbee_dio_output_t output) {


    return XB_OK;
}


xb_ret_t xb_init(int (*write)(uint8_t *buf, size_t len)) {

    // TODO: More stuff
    return XB_OK;
}





