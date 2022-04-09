#include "filesys.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int WRITEABLE = 0;
static FILE *current_file = NULL;
static char *PAGE_BUFFER = NULL;
static int PAGE_BUFFER_SIZE = 512;
static int8_t BUFFER_INDEX = 0;


FS_STATUS fs_new() {
    if (current_file != NULL && !WRITEABLE) {
        return FS_UNWRITABLE;
    } else if (current_file == NULL){
        current_file = fopen("log.csv", "w");
    } else if (WRITEABLE != 0) {
        fclose(current_file);
        current_file = fopen("log.csv", "w");
        BUFFER_INDEX = 0;
    }

    return FS_OK;
}

/**
 * Close the opened file
 * @return FS_STATUS
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
    if (len + BUFFER_INDEX > PAGE_BUFFER_SIZE) {
        uint16_t empty = PAGE_BUFFER_SIZE - BUFFER_INDEX;
        memcpy(PAGE_BUFFER + BUFFER_INDEX, data, empty);
    } else {
        memcpy(PAGE_BUFFER + BUFFER_INDEX, data, len);
    }

    BUFFER_INDEX += len;

    return FS_OK;
}


FS_STATUS fs_dump_files(FILE *descriptor) {


    return FS_OK;
}


void fs_toggle_overwrite() {
    switch (WRITEABLE) {
        case 0:
            WRITEABLE = 1;
            break;
        case 1:
            WRITEABLE = 0;
            break;

        default:
            WRITEABLE = 0;
            break;
    }
}

FS_STATUS fs_init(int can_write, int user_specified_buffer_size) {
    WRITEABLE = can_write;
    fs_toggle_overwrite();
    PAGE_BUFFER_SIZE = user_specified_buffer_size;

    return FS_OK;
}
