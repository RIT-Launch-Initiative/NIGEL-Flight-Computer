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
#include "xbee.h"

#define START_DELIMETER   0x7E
#define TX_FRAME_TYPE     0x10
#define RX_FRAME_TYPE     0x90
#define AT_CMD_FRAME_TYPE 0x17
#define RESERVED_VALUE    0xFEFF // in network order

// static buffer sizes
#define TX_BUFF_SIZE 1024 // bytes
#define RX_BUFF_SIZE 2048 // bytes

typedef struct {
    uint8_t start_delimiter;
    uint16_t length;
} __attribute__((packed)) xb_header_t;

typedef struct {
    xb_header_t header;
    uint8_t frame_type;
    uint8_t frame_id;
    uint64_t dst_address_64;
    uint16_t reserved;
    uint8_t radius;
    uint8_t options;
} __attribute__((packed)) xb_tx_frame_t;

typedef struct {
    xb_header_t header;
    uint8_t frame_type;
    uint64_t src_address_64;
    uint16_t reserved;
} __attribute__((packed)) xb_rx_frame_t;

typedef struct {
    xb_header_t header;
    uint8_t frame_type;
    uint8_t frame_id;
    uint64_t dst_address_64;
    uint16_t reserved;
    uint8_t options;
    uint8_t at_command[2];
} __attribute__((packed)) xb_at_frame_t;

int (*xb_write)(uint8_t *buf, size_t len);
void (*xb_delay)(uint32_t ms);

static uint64_t default_dst = 0xFFFF000000000000; // broadcast address in network order
static void (*rx_callback)(uint8_t *buff, size_t len);

static uint8_t tx_buff[TX_BUFF_SIZE];

xb_ret_t xb_send(uint8_t* data, size_t len) {
    return xb_sendto(default_dst, data, len);
}

xb_ret_t xb_sendto(uint64_t addr, uint8_t *data, size_t len) {
    xb_tx_frame_t *frame = (xb_tx_frame_t *) tx_buff;

    frame->header.start_delimiter = START_DELIMETER;
    // length = payload + frame - header
    frame->header.length = hton16(len + sizeof(xb_tx_frame_t) - sizeof(xb_header_t));
    frame->frame_type = TX_FRAME_TYPE;
    frame->frame_id = 0;
    frame->dst_address_64 = addr;
    frame->reserved = RESERVED_VALUE;
    frame->radius = 0;
    frame->options = 0x80;


    memcpy(tx_buff + sizeof(xb_tx_frame_t), data, len);

    uint8_t check = 0;
    for (size_t i = sizeof(xb_header_t); i < len + sizeof(xb_tx_frame_t); i++) {
        check += tx_buff[i];
    }

    check = 0xFF - check;
    memcpy(tx_buff + len + sizeof(xb_tx_frame_t), &check, 1);

    size_t write_len = len + sizeof(xb_tx_frame_t) + 1;
    if (xb_write(tx_buff, write_len) < write_len) {
        // write error
        return XB_ERR;
    }

    return XB_OK;
}

void xb_attach_rx_callback(void (*rx)(uint8_t *buff, size_t len)) {
    rx_callback = rx;
}


#define RX_BUFF_SIZE 2048 // bytes
static uint8_t rx_buff[RX_BUFF_SIZE];

void xb_raw_recv(uint8_t *buff, size_t len) {
    typedef enum {
        WAITING_FOR_FRAME,
        WAITING_FOR_LENGTH,
        READING_PAYLOAD,
        WAIT_FOR_FRAME_END
    } state_t;

    static size_t rx_index = 0;
    static size_t to_read; // bytes left of payload to read
    static size_t payload_size;

    static state_t state = WAITING_FOR_FRAME;
    static uint8_t check = 0;

    size_t i = 0;

    start_switch:
    switch(state) {
        case WAITING_FOR_FRAME:
            for(; i < len; i++) {
                if(buff[i] == START_DELIMETER) {
                    state = WAITING_FOR_LENGTH;
                    rx_index = 0;
                    i++;
                    break; // don't need to keep checking for delimeters
                }
            }

            if(state == WAITING_FOR_FRAME) {
                break;
            } // otherwise start parsing header

        case WAITING_FOR_LENGTH:
            for(; i < len; i++) {
                rx_buff[rx_index] = buff[i];
                rx_index++;
                if(rx_index == 2) {
                    i++;
                    payload_size = ntoh16(*((uint16_t*)rx_buff));
                    to_read = payload_size + 1; // read checksum too

                    // TODO maybe just get rid of this and read all kinds of frames
                    // then decide which callback to call based on frame id
                    // if(rx_buff[2] != RX_FRAME_TYPE) {
                    //     // wait for this frame to finish
                    //     state = WAIT_FOR_FRAME_END;
                    //     goto start_switch; // gross
                    // }

                    // start writing over the buffer again, already stored length
                    rx_index = 0;

                    state = READING_PAYLOAD;
                    break; // don't need to keep reading header
                }
            }

            if(state == WAITING_FOR_LENGTH) {
                break;
            }

        case READING_PAYLOAD:
            for(; i < len; i++) {
                rx_buff[rx_index++] = buff[i];
                to_read--;

                if(to_read == 0) {
                    uint8_t checksum = 0xFF - check;
                    if (checksum == rx_buff[rx_index - 1]) {
                        // pick a callback based on the frame type
                        switch(rx_buff[0]) {
                            case RX_FRAME_TYPE:
                                if(rx_callback) {
                                    rx_callback(rx_buff + 12, payload_size - 12);
                                }
                                break;
                            default:
                                // no callback
                                break;
                        }
                    } // else bad check, throwaway

                    // read a full frame, reset from the top
                    check = 0;
                    state = WAITING_FOR_FRAME;
                    goto start_switch;
                } else {
                    check += buff[i];
                }


                if(rx_index == RX_BUFF_SIZE) {
                    // can't read anymore, throw away packet
                    state = WAIT_FOR_FRAME_END;
                    goto start_switch;
                }
            }
            break; // should immediately fail next loop anyways
        case WAIT_FOR_FRAME_END:
            for(; i < len; i++) {
                // do nothing
                to_read--;

                if(to_read == 0) {
                    // restart now
                    state = WAITING_FOR_FRAME;
                    goto start_switch;
                }
            }
    }
}

void xb_set_default_dst(uint64_t addr) {
    default_dst = hton64(addr);
}

static xb_ret_t xb_at_cmd(const char cmd[2], const char *param) {
    xb_at_frame_t *frame = (xb_at_frame_t *) tx_buff;

    size_t param_size = strlen(param);

    frame->header.start_delimiter = START_DELIMETER;
    // length = frame - header + param
    frame->header.length = hton16(sizeof(xb_at_frame_t) - sizeof(xb_header_t) + param_size);
    frame->frame_type = AT_CMD_FRAME_TYPE;
    frame->frame_id = 0;
    frame->dst_address_64 = default_dst;
    frame->reserved = hton16(0xFFFE);
    frame->options = 0x02; // apply changes immediately on remote
    frame->at_command[0] = cmd[0];
    frame->at_command[1] = cmd[1];

    // copy parameter
    memcpy(tx_buff + sizeof(xb_at_frame_t), param, param_size);

    uint8_t check = 0;
    size_t i;
    for (i = sizeof(xb_header_t); i < sizeof(xb_at_frame_t) + param_size; i++) {
        check += tx_buff[i];
    }

    tx_buff[i] = 0xFF - check;

    if (xb_write(tx_buff, i + 1) < i + 1) {
        // write error
        return XB_ERR;
    }

    return XB_OK;
}

xb_ret_t xb_cmd_dio(xb_dio_t dio, xb_dio_output_t output) {
    char cmd[2];

    switch (dio) {
        case XB_DIO12:
            // P2
            cmd[0] = 'P';
            cmd[1] = '2';
            break;
        default:
            return XB_ERR;
    }

    // TODO I'm not sure if the parameter is passed as ASCII or binary
    char *param = "4";
    if (output == XB_DIO_HIGH) {
        param = "5";
    } // else low (4)

    return xb_at_cmd(cmd, param);
}

xb_ret_t xb_init(int (*write)(uint8_t *buf, size_t len), void (*delay)(uint32_t ms)) {
    xb_write = write;
    xb_delay = delay;

    // enter command mode
    if (xb_write((uint8_t*)"+++", 3) < 3) {
        // write failure
        return XB_ERR;
    }

    // the line should be silent for 1s
    // wait for 1.5s to be safe
    delay(1500);

    // send command to put into API mode
    const char *at_cmd = "ATAP1\r"; // API mode without escapes

    if (xb_write((uint8_t*)at_cmd, 6) < 6) {
        // write failure
        return XB_ERR;
    }

    // at this point we're in API mode

    return XB_OK;
}
