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
int fs_init(uint32_t (*read_fun) (uint8_t* buff, size_t len), uint32_t (*write_fun) (uint32_t page_num, uint32_t* buff, size_t len));

/**
 * Writes data into a buffer
 * @return status code
 */
int fs_write(uint32_t *data, size_t len);

/**
 * Reads data out from specific flight
 *
 * @return
 */
int fs_read(uint32_t flight_num);


/**
 * Writes buffer into a file
 * @return status code
 */
int fs_dump();

/**
 * Cleanup
 * @return status code
 */
int fs_close();

#endif //NIGEL_FLIGHT_COMPUTER_FS_H
