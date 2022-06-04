#include <stddef.h>
#include "fs.h"
#include "hashmap.h"

#define FILE_LIMIT 5 // TODO: Change this :)
#define INDEX_PAGE 0


static char *flights;
static int num_flights = 0;
static int num_pages = 0;
static char *buffer;
static int current_flight_len = 0;

static int (*read_out) (uint8_t* buff, size_t len);
static int (*write_out) (uint8_t* buff, size_t len);

/**
 * Initialize the fs
 * @return status code
 */
int fs_init(int (*read_fun) (uint8_t* buff, size_t len), int (*write_fun) (uint8_t* buff, size_t len)) {
    read_out = read_fun;
    write_out = write_fun;

    return 0;
}

int fs_read(int flight_num) {
    char *start_flight;
    char *end_flight;
    char *len_flight;

    for (int i = start_flight; i < len_flight; i++) {

    }

}

/**
 * Writes data into a buffer
 * @return status code
 */
int fs_write() {
    return 0;
}

/**
 * Writes buffer into a file
 * @return status code
 */
int fs_dump() {


    return 0;
}

/**
 * Closes file
 * @return status code
 */
int fs_close() {
    return 0;
}