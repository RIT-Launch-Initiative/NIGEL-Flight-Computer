#ifndef SYS_H
#define SYS_H

// init module
int sys_init();

// basic I/O (retargeted libc functions used by stdio)
int _write(int file, char *ptr, int len);
int _read(int file, char *ptr, int len);

#endif
