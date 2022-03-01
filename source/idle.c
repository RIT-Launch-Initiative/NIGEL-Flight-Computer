/*
*   Idle task
*/
#include "ts.h"

tiny_task_t idle_task;
int idle_ttid;

static void idle(tiny_task_t* task) {
    // TODO blink an LED or something

    task->start_time = ts_systime() + 100; // run in another 100ms
    return;
}

int idle_init() {
    idle_task.start_time = ts_systime();
    idle_task.default_priority = IDLE_PRIORITY;
    idle_task.task = &idle;

    idle_ttid = ts_add(&idle_task);

    if(idle_ttid == TS_ERR_TTID) {
        return -1;
    }

    return 1;
}
