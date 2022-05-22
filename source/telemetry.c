/*
*   Telemetry bufferer
*
*   Will Merges @ RIT Launch Initiative
*/
#include <stdlib.h>
#include <stdint.h>

#include "telemetry.h"
#include "ts.h"
#include "queue.h"
#include "hashmap.h"
#include "sio.h"

// actual rates in Hz
uint8_t tlm_frequency_map[NUM_TELEMETRY_RATES] =
{
    1,
    10,
    20
};

static int xb_fd;

struct task_info {
    tiny_task_t task;
    queue_t* q;
    hashmap_t* hm;
    long int period; // ms
};

struct task_info tasks[NUM_TELEMETRY_RATES];


static void tlm_task(tiny_task_t* task) {
    struct task_info* info = task->user_data;
    tlm_msg_t* msg;

    // dump the buffer
    while(!QUEUE_EMPTY(info->q)) {
        msg = q_dequeue(info->q); // this should never be NULL (since queue is not empty!)
        sio_write(xb_fd, (char*)msg->buff, msg->len);
        hm_rm(info->hm, msg->stream_id);
    }

    task->start_time = ts_systime() + info->period;
}

int tlm_buffer(tlm_msg_t* msg) {
    struct task_info* info = &tasks[msg->rate];

    if((void*)(1) == hm_get(info->hm, msg->stream_id)) {
        // we already have an old entry here, replace it
        hm_rm(info->hm, msg->stream_id);
    }

    // don't need to add a value to the map since we're using it like a set
    hm_add(info->hm, msg->stream_id, (void*)1);

    return q_enqueue(info->q, (void*)msg);
}

int tlm_init() {
    xb_fd = sio_search_name("xbee_uart");
    if(xb_fd == -1) {
        return -1;
    }

    struct task_info info;
    for(int i = 0; i < NUM_TELEMETRY_RATES; i++) {
        info = tasks[i];

        info.task.default_priority = MEDIUM_PRIORITY; // TODO higher? lower?
        info.task.task = &tlm_task;
        info.task.user_data = &info;

        if(TS_ERR_TTID == ts_add(&(info.task))) {
            return -1;
        }

        info.q = q_mkqueue(NULL);

        if(NULL == info.q) {
            return -1;
        }

        // TODO change size?
        info.hm = hm_create(HASHMAP_DEFAULT_SIZE, HASHMAP_DEFAULT_BUCKET_SIZE);

        if(NULL == info.hm) {
            return -1;
        }

        info.period = 1000 / tlm_frequency_map[i]; // ms
    }

    return 0;
}
