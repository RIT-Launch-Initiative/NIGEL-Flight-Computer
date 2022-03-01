/*
*   Setup communication stack
*   Initializes communication layers and connects them (sio -> xbee -> gcmd)
*
*   Will Merges @ RIT Launch Initiative
*/
#ifndef COMM_H
#define COMM_H

// initialize the communication stack
// return -1 on failure, 1 otherwise
int comm_init();

#endif
