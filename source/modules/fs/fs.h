/**
 * File System
 *
 * Aaron Chan
 */

#ifndef NIGEL_FLIGHT_COMPUTER_FS_H
#define NIGEL_FLIGHT_COMPUTER_FS_H

/**
 * Initialize the fs
 * @return status code
 */
int fs_init();

/**
 * Writes data into a buffer
 * @return status code
 */
int fs_write();

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
