#include "filesys.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FILENAME_SIZE 11 // logXXX.csv

static int writeable = 0;
static FILE *current_file = NULL;
static int file_index = 0;

FS_STATUS fs_new() {
    char filename[FILENAME_SIZE];
    sprintf(filename, "log%03d.csv", file_index);

    if (current_file != NULL && !writeable) {
        return FS_UNWRITABLE;
    }

    current_file = fopen(filename, "w");

    return FS_OK;
}

/**
 * Close the opened file
 * @return
 */
FS_STATUS fs_close() {
    if (current_file == NULL) {
        return FS_UNOPENED;
    }
    fclose(current_file);
    current_file = NULL;

    return FS_OK;
}


FS_STATUS fs_write(uint8_t *data, uint16_t len) {
    if (current_file == NULL) {
        return FS_UNOPENED;
    }

    fwrite(data, 1, len, current_file);
    return FS_OK;
}


FS_STATUS fs_dump_files(FILE *descriptor) {

    return FS_OK;
}


void fs_toggle_overwrite() {
    switch (writeable) {
        case 0:
            writeable = 1;
            break;
        case 1:
            writeable = 0;
            break;
    }
}


FS_STATUS fs_wipe() {

    return FS_OK;
}


FS_STATUS fs_init(int can_write) {
    writeable = can_write;
    fs_toggle_overwrite();

    return FS_OK;
}
