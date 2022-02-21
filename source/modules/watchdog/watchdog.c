#include "watchdog.h"
#include "watchdog_conf.h"
#include "main.h"
#include "tim.h"
#include <string.h>

static void (*hooks[NUM_WATCHDOGS]) ();
static int counter_value[NUM_WATCHDOGS];

void wd_pet(int wd) {
    if(wd >= NUM_WATCHDOGS || wd < 0) {
        // invalid
        return;
    }

    // turn timer off
    HAL_TIM_Base_Stop_IT(wd_timers[wd]);

    // reset counter
    wd_timers[wd]->Instance->CNT = counter_value[counter_value[wd]];

    // turn timer back on
    HAL_TIM_Base_Start_IT(wd_timers[wd]);
}

void wd_set_counter(int wd, uint32_t cnt) {
    if(wd >= NUM_WATCHDOGS || wd < 0) {
        // invalid
        return;
    }

    counter_value[wd] = cnt;

    // reset the timer
    wd_pet(wd);
}


void wd_attach_hook(int wd, void (*hook_func) ()) {
    if(wd >= NUM_WATCHDOGS || wd < 0) {
        // invalid
        return;
    }

    hooks[wd] = hook_func;
}

// function called by interrupt for timer
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    // find which timer went off
    size_t i;
    for(i = 0; i < NUM_WATCHDOGS; i++) {
        if(wd_timers[i] == htim) {
            break;
        }
    }

    if(i == NUM_WATCHDOGS) {
        // not a timer we're tracking
        return;
    }

    // call the hook function for this watchdog if it exists
    if(hooks[i]) {
        hooks[i]();
    }

    // HAL should take care of the rest of it for us
}

int wd_search_name(const char* name) {
    int wd = -1;
    for(size_t i = 0; i < NUM_WATCHDOGS; i++) {
        if(!strcmp(name, wd_names[i])) {
            wd = i;
        }
    }

    return wd;
}
