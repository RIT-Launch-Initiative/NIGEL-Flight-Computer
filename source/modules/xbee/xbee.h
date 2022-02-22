/*
*   XBee API mode external functions
*
*   Will Merges @ RIT Launch Initiative
*   2022
*/
#ifndef XBEE_H
#define XBEE_H

#include <stdint.h>
#include <stlib.h>

#define XBEE_BROADCAST_ADDR 0x000000000000FFFF

typedef enum {
    XB_OK,
    XB_ERR
} xb_ret_t;

// init function
// 'write' is a function that the API will use to output data to the XBee
// NOTE: places the XBee in API mode, 
//       this function must be called within 1s of power up or the XBee 
//       cannot be placed in command mode
xb_ret_t xb_init(int (*write) (uint8_t* buff, size_t len));

// function that should be called when any data is received from the XBee (either over serial or SPI)
// needs to be called by lower layer
void xb_raw_recv(uint8_t* buff, size_t len)

// attach a callback function to call when an rx frame is received
// 'buff' points to the payload of length 'len' in the frame
void xb_attach_rx_callback(void (*rx) (uint8_t* buff, size_t len));

// set the destination address of transmitted packets
// NOTE: default address is broadcast
void xb_set_dst(uint64_t addr);

// transmit data
xb_ret_t xb_tx(uint8_t* data, size_t len);

typedef enum {
    XBEE_DIO0,
    XBEE_DIO1,
    XBEE_DIO3
} xbee_dio_t;

typedef enum {
    XBEE_DIO_HIGH,
    XBEE_DIO_LOW
} xbee_dio_output_t;

// remotely command digital I/O
xb_ret_t xb_cmd_dio(xbee_dio_t dio, xbee_dio_output_t output);

#endif
