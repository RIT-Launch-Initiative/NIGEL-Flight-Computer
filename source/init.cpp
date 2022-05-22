#include <stdlib.h>
#include <stdio.h>
#include "main.h"

extern "C" {
    #include "ts.h"
    #include "sio.h"
    #include "gcmd.h"
    #include "comm.h"
    #include "idle.h"
    #include "telemetry.h"
}

// init function signature
// must return -1 on error, anything else on success
typedef int (*init_handler_t)();

// init functions that need to be called
// order is important
// whatever initializes printf output MUST be at index 0
init_handler_t init_functions[] =
{
    idle_init,
    comm_init,
    tlm_init,
    NULL
};

// needed by scheduler
long int ts_systime() {
    return (long int)HAL_GetTick();
}

// this is the entry point of the program after STM32 autogenerated initializations are complete
// NOTE: init should not return
void init() {
    size_t i = 0;
    while(init_functions[i]) {
        if(init_functions[i]() == -1) {
            // failed to initialize
            // try and write a debug message, this requires printf to work however
            // printf initialized at index 0
            if(i) {
                printf("failed to initialize routine at index: %u\r\n", i);
            } // otherwise we're borked and can't output why
        }
        i++;
    }

    // broken or not, here we go
    ts_schedule(NULL, 0);

    while(1) {};
}
