#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "xbee.c"

#define TEST_START_DELIMETER      0x7E
#define TEST_RX_FRAME_TYPE        0x90
#define TEST_BROADCAST_ADDR       0xFF
#define TEST_RESERVED_B1          0xFF
#define TEST_RESERVED_B2          0xFE
#define TEST_RCV_OPTION           0x80


void rx_print_data(uint8_t *data, size_t length) {
    printf("Received data: ");
    for (uint8_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    xb_attach_rx_callback(&rx_print_data);

    uint8_t TEST_RX_PACKET[] = {0x67, 0x61, 0x72, 0x62, 0x61, 0x67, 0x65, // Garbage data
                                TEST_START_DELIMETER, TEST_RX_FRAME_TYPE, TEST_BROADCAST_ADDR,
                                TEST_BROADCAST_ADDR,
                                TEST_BROADCAST_ADDR, TEST_BROADCAST_ADDR,
                                TEST_BROADCAST_ADDR, TEST_BROADCAST_ADDR, TEST_BROADCAST_ADDR,
                                TEST_BROADCAST_ADDR, TEST_RCV_OPTION, TEST_RESERVED_B1,
                                TEST_RESERVED_B2, // Pre-payload data
                                0x69, 0x69, 0x69, 0x69, // Payload data
                                0xEF // Checksum EOF. 0xff - 16 bytes from
    };


    xb_raw_recv(TEST_RX_PACKET, sizeof(TEST_RX_PACKET));


    return 0;
}




