/**
 * File System for writing flight data
 *
 * @author Aaron Chan
 */

#ifndef NIGEL_FLIGHT_COMPUTER_FILESYS_H
#define NIGEL_FLIGHT_COMPUTER_FILESYS_H

#include <stdio.h>

typedef enum {
    FS_OK,
    FS_FULL,
    FS_UNOPENED,
    FS_NOT_FOUND,
    FS_UNWRITABLE,
} FS_STATUS;

/**
 * Open a new file for writing data for a new flight.
 * @return FS Status
 */
FS_STATUS fs_new();

/**
 * Close the opened file
 * @return
 */
FS_STATUS fs_close();

/**
 * Write bytes to file
 * @param data
 * @param len
 * @return
 */
FS_STATUS fs_write(uint8_t *data, uint16_t len);

/**
 * Dump files out to the file descriptor
 * @param descriptor
 * @return FS_STATUS
 */
FS_STATUS fs_dump_files(FILE *descriptor);

/**
 * Allow files to be overwritten if out of space.
 */
void fs_toggle_overwrite();

/**
 * Initialize the file system.
 * @return FS_STATUS
 */
FS_STATUS fs_init();

#endif //NIGEL_FLIGHT_COMPUTER_FILESYS_H
