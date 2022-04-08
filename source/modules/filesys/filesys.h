#ifndef NIGEL_FLIGHT_COMPUTER_FILESYS_H
#define NIGEL_FLIGHT_COMPUTER_FILESYS_H

#include <stdio.h>

typedef enum {
    FS_OK,
    FS_FULL,
    FS_UNOPENED,
    FS_NOT_FOUND
} FS_STATUS;

/**
 * Open a new file for writing data for a new flight.
 * @return FS Status
 */
FS_STATUS fs_new_file();


/**
 * Open an existing file for writing data.
 * @param filename The name of the file to open.
 * @return FS Status
 */
FS_STATUS fs_open_file(char *filename);

/**
 * Close the currently open file.
 *
 * @return FS Status
 */
FS_STATUS fs_close_file();

/**
 * Dump files into a descriptor
 * @param descriptor
 * @return FS Status
 */
FS_STATUS fs_dump_files(FILE *descriptor);

/**
 * Wipes all flight data
 * @return
 */
FS_STATUS fs_wipe();

#endif //NIGEL_FLIGHT_COMPUTER_FILESYS_H
