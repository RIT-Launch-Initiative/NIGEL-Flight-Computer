#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "net.h"
#include "xbee.h"

#define TEST_START_DELIMETER      0x7E
#define TEST_RX_FRAME_TYPE        0x90
#define TEST_ADDR                 0xCF
#define TEST_RESERVED_B1          0xFF
#define TEST_RESERVED_B2          0xFE
#define TEST_RCV_OPTION           0x80
#define TEST_LENGTH_B1            0x00
#define TEST_LENGTH_B2            0x10 // 16


void rx_print_data(uint8_t *data, size_t length) {
    printf("Received data: ");
    for (uint8_t i = 0; i < length; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    xb_attach_rx_callback(&rx_print_data);

    uint8_t TEST_RX_PACKET[] = {0x67, 0x61, 0x72, 0x62, 0x61, 0x67, 0x65, // Garbage data
                                TEST_START_DELIMETER, // start delim
                                TEST_LENGTH_B1, TEST_LENGTH_B2, // length (16)
                                TEST_RX_FRAME_TYPE, // frame type
                                TEST_ADDR, TEST_ADDR, TEST_ADDR, TEST_ADDR, // addr high
                                TEST_ADDR, TEST_ADDR, TEST_ADDR, TEST_ADDR, // addr low
                                TEST_RESERVED_B1, TEST_RESERVED_B2, // reserved
                                0x00, // receive options
                                0x69, 0x69, 0x69, 0x69, // payload
                                0x00 // checksum to calculate
    };

    // calculate checksum (b/w length and checksum fields)
    uint8_t check = 0;
    for(size_t i = 10; i < sizeof(TEST_RX_PACKET) - 1; i++) {
        check += TEST_RX_PACKET[i];
    }

    check = 0xFF - check;
    TEST_RX_PACKET[sizeof(TEST_RX_PACKET) - 1] = check;

    // test with one chunk
    printf("should print once\n");
    xb_raw_recv(TEST_RX_PACKET, sizeof(TEST_RX_PACKET));
    printf("\n");

    // test with two chunks
    printf("should print once\n");
    xb_raw_recv(TEST_RX_PACKET, sizeof(TEST_RX_PACKET) - 15);
    xb_raw_recv(TEST_RX_PACKET + sizeof(TEST_RX_PACKET) - 15, 15);
    printf("\n");

    // test with single bytes received at a time
    printf("should print once\n");
    for(size_t i = 0; i < sizeof(TEST_RX_PACKET); i++) {
        xb_raw_recv(TEST_RX_PACKET + i, 1);
    }
    printf("\n");

    // change the frame id to not an rx frame
    TEST_RX_PACKET[10] = 0x91;
    // shouldn't print
    xb_raw_recv(TEST_RX_PACKET, sizeof(TEST_RX_PACKET));

    return 0;
}
