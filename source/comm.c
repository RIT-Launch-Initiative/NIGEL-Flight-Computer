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

static int xb_fd;
static tiny_task_t task;
static int ttid;

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

    // read all available data from the sio layer
    int len = sio_read(xb_fd, (char*)buffer, sio_available(xb_fd));
    if(len == -1) {
        // read fail
        return;
    }

    // send the data up to the xbee layer
    xb_raw_recv(buffer, len);
}

int comm_init() {
    // initialize the task
    task.default_priority = SLEEP_PRIORITY;
    task.task = &comm_task;

    ttid = ts_add(&task);

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
    xb_attach_rx_callback(&gcmd_parse);

    // data is sent from sio to xbee
    sio_attach_callback(xb_fd, xbee_cb);

    // xbee can already send data down to sio

    return 1;
}
