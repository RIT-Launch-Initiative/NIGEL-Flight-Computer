#ifndef WATCHDOG_CONFIG_H
#define WATCHDOG_CONFIG_H

#include "tim.h"

#define NUM_WATCHDOGS 1

static TIM_HandleTypeDef* wd_timers[NUM_WATCHDOGS] =
{
    &htim2
};

static const char* wd_names[NUM_WATCHDOGS] = {
    "telemetry_watchdog"
};

#endif
