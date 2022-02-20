#ifndef SYS_H
#define SYS_H

// init module
int sys_init();

// find how many bytes are available on an I/O character device
size_t io_available(int fd);

// basic character I/O (retargeted libc functions used by stdio)
// shouldn't need to use these, use stdio functions instead
int _write(int fd, char *buff, int len);
int _read(int fd, char *buff, int len);

#endif
