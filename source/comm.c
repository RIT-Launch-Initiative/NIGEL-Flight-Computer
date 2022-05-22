/*
*   Setup communication stack
*   Initializes communication layers and connects them (sio -> xbee -> gcmd)
*
*   Will Merges @ RIT Launch Initiative
*/
#include <stdint.h>
#include <stdlib.h>

#include "comm.h"
#include "xbee.h"
#include "gcmd.h"
#include "spinlock.h"
#include "ts.h"
#include "sio.h"
#include "telemetry.h"
#include "udp.h"

static int xb_fd;
static tiny_task_t task;

static xb_rx_request req;

// function that XBee layer calls to write data out the UART
static int xbee_write(uint8_t* buff, size_t len) {
    return sio_write(xb_fd, (char*)buff, len);
}

// function sio calls when it has data for the XBee
static void xbee_cb() {
    // schedule a read from the sio layer to the XBee layer
    task.start_time = ts_systime();
    task.priority = HIGH_PRIORITY;
}

// task that moves data from sio layer to XBee layer
uint8_t buffer[2048];
static void comm_task(tiny_task_t* t) {
    // we don't need to explicitly sleep since that's our default priority after executing

    // TODO we can eliminate some of these copies
    // we shouldn't need to copy 3 times
    // we copy from HAL -> sio -> here -> Xbee (no copy to gcmd)
    // investigate a way to copy from HAL into a single buffer than everyone can work off of (tricky to get around the ring buffer)
    // UPDATE: removed the copy from here to xbee (now we just copy from HAL and then from sio)

    // read all available data from the sio layer
    // NOTE: we can queue more since req has a requested length field
    while(sio_available(xb_fd)) {
        int len = sio_read(xb_fd, (char*)(req.buff), req.len);
        if(len == -1) {
            // read fail
            return;
        }

        // send the data up to the xbee layer
        xb_rx_complete(&req);
    }

    // sleep ourselves until the next serial read
    t->priority = SLEEP_PRIORITY;
}

typedef struct {
    udp_header_t udp;
    uint32_t uptime;
    uint32_t heartbeat_count;
} __attribute__((packed)) heartbeat_packet_t;

heartbeat_packet_t hb;
tlm_msg_t hb_msg;

// save the source address as the default destination address for telemetyr packets
// also sends a telemetry message back just containing the uptime and heartbeat count
void comm_heartbeat(uint16_t unused, void* addr_info) {
    uint64_t src_addr = (uint64_t)addr_info;
    xb_set_default_dst(src_addr);

    hb.uptime = ts_systime();
    hb.heartbeat_count++;
    hb.udp.checksum = 0;
    hb.udp.checksum = udp_calculate_checksum((uint8_t*)&hb, sizeof(hb));

    tlm_buffer(&hb_msg);
}

int comm_init() {
    // initialize the task
    task.default_priority = SLEEP_PRIORITY;
    task.task = &comm_task;

    int ttid = ts_add(&task);

    if(ttid == TS_ERR_TTID) {
        // failed to put on scheduler
        return -1;
    }

    // initialize serial IO module
    if(sio_init() != 1) {
        return -1;
    }

    // get the file descriptor the XBee UART is on
    xb_fd = sio_search_name("xbee_uart");
    if(xb_fd == -1) {
        return -1;
    }

    // initialize XBee
    // data from sio is sent up to XBee
    if(xb_init(&xbee_write, &spinlock) != XB_OK) {
        return -1;
    }

    // initialize gcmd layer
    if(gcmd_init() != 1) {
        return -1;
    }

    // packets are sent up from xbee to gcmd
    xb_attach_rx_callback((void (*)(uint8_t*, size_t, uint64_t))(&gcmd_parse));

    // kick off XBee reading
    // NOTE: must be before we initialize the sio callback!
    // since req is uninitialized until after this call
    xb_rx_complete(&req);

    // data is sent from sio to xbee
    sio_attach_callback(xb_fd, xbee_cb);

    // xbee can already send data down to sio

    // set up heartbeat telemetry message
    hb_msg.buff = (uint8_t*)&hb;
    hb_msg.len = sizeof(hb);
    hb_msg.stream_id = HEARTBEAT_STREAM;
    hb_msg.rate = HEARTBEAT_RATE;

    hb.heartbeat_count = 0;

    return 1;
}
