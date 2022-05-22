/*
*   Flight Termination System source
*
*   Will Merges @ RIT Launch Initiative
*/
#include "fts.h"
#include "telemetry.h"
#include "udp.h"
#include "net.h"
#include "ts.h"
#include <stdint.h>

typedef struct {
    udp_header_t udp;
    long int uptime; // ms
    uint16_t state;
} __attribute__((packed)) fts_packet_t;

static fts_packet_t state;
tlm_msg_t fts_msg;

void fts_send_tlm() {
    state.uptime = ts_systime();
    state.udp.checksum = 0;
    state.udp.checksum = udp_calculate_checksum((uint8_t*)&state, sizeof(state));

    // TODO error checking?
    tlm_buffer(&fts_msg);
}

void fts_set_state(uint16_t state, void* unused_src_addr) {
    switch(state) {
        case FTS_DISARMED:
            fts_disarm();
            break;
        case FTS_ARMED:
            fts_arm();
            break;
        case FTS_TERMN:
            fts_termn();
            break;
    }

    fts_send_tlm();
}

void fts_arm() {
    state.state = FTS_ARMED;
}

void fts_disarm() {
    state.state = FTS_DISARMED;
}

void fts_termn() {
    if(state.state == FTS_ARMED) {
        // TODO boom

        state.state = FTS_TERMN;
    }
}

int fts_init() {
    state.state = FTS_DISARMED;

    state.udp.src_port = ntoh16(FTS_DST_PORT);
    state.udp.dst_port = ntoh16(FTS_SRC_PORT);
    state.udp.len = sizeof(state) - sizeof(udp_header_t);

    fts_msg.buff = (uint8_t*)&state;
    fts_msg.len = sizeof(state);
    fts_msg.stream_id = FTS_STREAM;

    return 0;
}
