#include "runcam.h"

typedef struct {
    RX_HEADER,
    RX_PROTO_VER,
    RX_FEATURE,
    RX_CRC8
} rc_response_packet_t;

rc_ret_t rc_init() {
    return RC_OK;
}

rc_ret_t rc_exec_cmd(rc_cmd_t cmd) {
    rc_response_packet_t packet;
    packet.RX_HEADER = 0x00;
    packet.RX_PROTO_VER = NULL; // TODO: Figure it out
    packet.RX_FEATURE = cmd;
    packet.RX_CRC8 = rc_crc_checksum(0, 'a') // TODO: Wack

    return RC_SUCCESS;
}


uint8_t rc_crc_checksum(uint8_t crc, unsigned char a) {
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }

    return crc;

}