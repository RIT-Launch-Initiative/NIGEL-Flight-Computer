#ifndef XBEE_H
#define XBEE_H

#define XB_TRANSMIT 0x10

// Escape Characters
#define XB_FRAME_DELIMITER 0x7e
#define XB_ESCAPE 0x7D
#define XB_ON 0x11
#define XB_OFF 013

typedef enum {
    XB_ERR,
    XB_OK
} xb_ret_t;

typedef enum {
    XB_IO1,
    XB_IO2
} xb_io_t;


typedef struct {
    uint8_t start_delimiter;
    uint16_t length;
    uint8_t frame_type;
    uint64_t dst_address_64;
    uint16_t dst_address_16;
    uint8_t radius;
    uint8_t options;
    uint64_t payload; // Variable amount of data
    uint8_t checksum;
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

extern int _xb_write(uint8_t *buf, size_t len);

// Initialize XBee Module
void xb_init();

// Transmit data from XBee
xb_ret_t xb_transmit(uint8_t radius, void *payload, int (*write)(uint8_t *buf, size_t len));

// Receive data to XBee
xb_ret_t xb_receive();


#endif