/**
 * File System
 *
 * Aaron Chan
 */

#ifndef NIGEL_FLIGHT_COMPUTER_FS_H
#define NIGEL_FLIGHT_COMPUTER_FS_H

#include <stdint.h>

/**
 * Initialize the fs
 * @return status code
 */
int fs_init(int (*read_fun) (uint8_t* buff, size_t len), int (*write_fun) (uint8_t* buff, size_t len));

/**
 * Writes data into a buffer
 * @return status code
 */
int fs_write(char *data, size_t len);

/**
 * Reads data out from specific flight
 *
 * @return
 */
int fs_read(int flight_num);


/**
 * Writes buffer into a file
 * @return status code
 */
int fs_dump();

/**
 * Closes file
 * @return status code
 */
int fs_close();

#endif //NIGEL_FLIGHT_COMPUTER_FS_H
