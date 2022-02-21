/*
*   Watchdog implementation using HAL timer
*
*   NOTE: any timer used should be setup in count DOWN mode
*         e.g. interrupt generated when counter hits 0
*
*   NOTE: assumes HAL timer setup with NO register callbacks
*         e.g. relies on the default function HAL_TIM_PeriodElapsedCallback to
*         be called on interrupt
*
*   author: Will Merges
*/
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdint.h>

// reset the watchdog by 'petting' it
// 'wd' is a watchdog descriptor, corresponds to index in 'watchdog_conf.h'
void wd_pet(int wd);

// set the counter time for the watchdog counter
// 'cnt' is in values of ticks, where ticks is the clock rate into the timer (including prescaling/internal division)
// NOTE: resets the timer
void wd_set_counter(int wd, uint32_t cnt);

// attach a function to call when the watchdog goes off
void wd_attach_hook(int wd, void (*hook_func) ());

// search for the watchdog descriptor matching a name
// names correspond to names defined in 'sio_config.h'
// returns -1 on no match, matching fd otherwise
int wd_search_name(const char* name);

#endif
