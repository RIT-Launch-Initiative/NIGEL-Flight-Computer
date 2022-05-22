/*
*   Setup communication stack
*   Initializes communication layers and connects them (sio -> xbee -> gcmd)
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef COMM_H
#define COMM_H

// initialize the communication stack
// returns -1 on failure, 1 otherwise
int comm_init();

// request a heartbeat to be sent over telemetry
void comm_heartbeat(uint16_t state, void* addr_info);

#endif
