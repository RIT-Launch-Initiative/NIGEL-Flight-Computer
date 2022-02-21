#ifndef SYS_H
#define SYS_H

#include "main.h"

// 'fd' refers to a descriptor corresponding to the mapping of 'uarts' in sio_config.h

// init module
int sio_init();

// find how many bytes are available on an I/O character device
size_t sio_available(int fd);

// basic character I/O (retargeted libc functions used by stdio)
// shouldn't need to use these, use stdio functions instead
int sio_write(int fd, char *buff, int len);
int sio_read(int fd, char *buff, int len);

// attach a callback function to a specific descriptor
void sio_attach_callback(int fd, void (*cb_func) ());

// search for the file descriptor matching a name
// names correspond to names defined in 'sio_config.h'
// returns -1 on no match, matching fd otherwise
int sio_search_name(const char* name);

#endif
