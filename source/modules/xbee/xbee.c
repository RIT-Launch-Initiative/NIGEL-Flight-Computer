/**
 * XBEE Radio Library
 *
 * @author Aaron Chan
 */
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "net.h"
#include "spinlock.h"
#include "xbee.h"

typedef struct {
    uint8_t start_delimiter;
    uint16_t length;
} xb_header_t;

typedef struct {
    xb_header_t header;
    uint8_t frame_type;
    uint64_t dst_address_64;
    uint16_t reserved;
    uint8_t radius;
    uint8_t options;
} xb_tx_frame_t;

typedef struct {
    xb_header_t header;
    uint8_t frame_type;
    uint64_t src_address_64;
    uint16_t reserved;
} xb_rx_frame_t;

typedef struct {
    xb_header_t header;
    uint8_t frame_type;
    uint8_t frame_id;
    uint64_t dst_address_64;
    uint16_t reserved;
    uint8_t options;
    uint8_t at_command[2];
} xb_at_frame_t;

int (*xb_write)(uint8_t *buf, size_t len);
static uint8_t tx_buff[1024];
static uint8_t rx_buff[1024];
static void (*rx)(uint8_t *buff, size_t len) rx_callback;

xb_ret_t xb_tx(uint8_t *data, size_t len) {
    xb_tx_frame_t *frame = (xb_tx_frame_t *) tx_buff;

    frame->header.start_delimiter = 0x7E;
    // length = payload + frame - header
    frame->header.length = hton16(len + sizeof(xb_tx_frame_t) - sizeof(xb_header_t));
    frame->frame_type = 0x10;
    frame->dst_address_64 = dst_addr;
    frame->reserved = hton16(0xFFFE);
    frame->radius = 0;
    frame->options = 0x80;


    memcpy(tx_buff + sizeof(xb_tx_frame_t), data, len);

    uint8_t check = 0;
    for (size_t i = sizeof(xb_header_t); i < len + sizeof(xb_tx_frame_t); i++) {
        check += tx_buff[i];
    }

    check = 0xff - check;
    memcpy(tx_buff + len  + sizeof(xb_tx_frame_t), &check, 1);

    size_t write_len = len + sizeof(xb_tx_frame_t) + 1;
    if(xb_write(tx_buff, write_len) < write_len) {
        // write error
        return XB_ERR;
    }

    return XB_OK;
}

void xb_attach_rx_callback(void (*rx)(uint8_t *buff, size_t len)) {
    rx_callback = rx;
}


void xb_raw_recv(uint8_t *buff, size_t len) {
    // TODO
}

void xb_set_dst(uint64_t addr) {
    dst_addr = addr;
}

static xb_ret_t xb_at_cmd(const char[2] cmd, const char* param) {
    xb_at_frame_t *frame = (xb_at_frame_t *) tx_buff;

    size_t param_size = strlen(param);

    frame->header.start_delimiter = 0x7E;
    // length = frame - header + param
    frame->header.length = hton16(sizeof(xb_at_frame_t) - sizeof(xb_header_t) + param_size);
    frame->frame_type = 0x17;
    frame->frame_id = 0;
    frame->dst_address_64 = dst_addr;
    frame->reserved = hton16(0xFFFE);
    frame->options = 0x02; // apply changes immediately on remote
    frame->at_command[0] = cmd[0];
    frame->at_command[1] = cmd[1];

    // copy parameter
    memcpy(tx_buff + sizeof(xb_at_frame_t), param, param_size);

    uint8_t check = 0;
    size_t i;
    for(i = sizeof(xb_header_t); i < sizeof(xb_at_frame_t) + param_size; i++) {
        check += at_buff[i];
    }

    tx_buff[i] = 0xFF - check;

    size_t len = sizeof(xb_at_frame_t) + param_size + 1;
    if(xb_write(tx_buff, len) < len) {
        // write error
        return XB_ERR;
    }

    return XB_OK;
}

xb_ret_t xb_cmd_dio(xb_dio_t dio, xb_dio_output_t output) {
    char cmd[2];

    switch(dio) {
        case XB_DIO12:
            // P2
            cmd[0] = 'P';
            cmd[1] = '2';
            break;
        default:
            return XB_ERR;
    }

    // TODO I'm not sure if the parameter is passed as ASCII or binary
    char* param = "4";
    if(output == XB_DIO_HIGH) {
        param = "5";
    } // else low (4)

    return xb_at_cmd(cmd, param);
}

xb_ret_t xb_init(int (*write)(uint8_t *buf, size_t len)) {
    xb_write = write;

    // enter command mode
    if(xb_write("+++", 3) < 3) {
        // write failure
        return XB_ERR;
    }

    // the line should be silent for 1s
    // wait for 1.5s to be safe
    spinlock(1500);

    // send command to put into API mode
    const char* at_cmd = "ATAP1\r"; // API mode without escapes

    if(xb_write(at_cmd, 6) < 6) {
        // write failure
        return XB_ERR;
    }

    // at this point we're in API mode

    return XB_OK;
}
