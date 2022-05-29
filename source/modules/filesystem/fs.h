/**
 * File System
 *
 * Aaron Chan
 */

#ifndef NIGEL_FLIGHT_COMPUTER_FS_H
#define NIGEL_FLIGHT_COMPUTER_FS_H

/**
 * Initialize the filesystem
 * @return status code
 */
int fs_init();

/**
 * Writes data into a buffer
 * @return status code
 */
int fs_write();

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
