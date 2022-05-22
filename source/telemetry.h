/*
*   Telemetry bufferer
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include <stdlib.h>

// telemetry stream IDs
#define FTS_STREAM 0
#define FTS_RATE RATE_20HZ

#define HEARTBEAT_STREAM 1
#define HEARTBEAT_RATE RATE_20HZ

// initializes telemetry bufferer tasks
// returns -1 on failure, 1 otherwise
int tlm_init();

// different telemetry rates
typedef enum {
    RATE_1HZ,
    RATE_10HZ,
    RATE_20HZ,
    NUM_TELEMETRY_RATES
} tlm_rate_t;

// defines how a message is passed to be buffered
typedef struct {
    uint8_t* buff;
    size_t len;
    uint32_t stream_id;
    tlm_rate_t rate;
} tlm_msg_t;

// buffers a message to be sent at a certain rate
// if a message with the same stream_id is already buffered, this call fails
// the message will be buffered and sent at the specified rate
// returns 0 on success, -1 on error
int tlm_buffer(tlm_msg_t* msg);

#endif
