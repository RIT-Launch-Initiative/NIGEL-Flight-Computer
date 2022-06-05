#include <stddef.h>
#include "fs.h"
#include "hashmap.h"

#define FILE_LIMIT 5 // TODO: Change this :)
#define INDEX_PAGE 0

static char *flights;
static uint32_t num_flights = 0;
static uint32_t num_pages = 0;
static char *buffer;
static uint32_t buffer_index = 0;
static int current_flight_len = -1;

static uint32_t (*read_out) (uint8_t* buff, size_t len);
static uint32_t (*write_out) (uint8_t* buff, size_t len);

/**
 * Initialize the fs
 * @return status code
 */
int fs_init(uint32_t (*read_fun) (uint8_t* buff, size_t len), uint32_t (*write_fun) (uint8_t* buff, size_t len)) {
    read_out = read_fun;
    write_out = write_fun;

    current_flight_len++;

    return 0;
}

int fs_read(uint32_t flight_num) {
    if (flight_num > num_flights) {
        return 1;
    }

    char *start_flight = flights + (num_flights - 1);
    char *end_flight = flights + num_flights;
    uint32_t len_flight = end_flight - start_flight;
    uint8_t flight_buff[len_flight];

    for (int i = 0; i < len_flight; i++) {
        flight_buff[i] = *start_flight + i;
    }

    read_out(flight_buff, len_flight); // TODO: Error handling

    return 0;
}

/**
 * Writes data into a buffer
 * @return status code
 */
int fs_write(char *data, size_t len) {
    char *sub_buffer = buffer + buffer_index;

    for (int i = 0; i < len; i++) {
        sub_buffer = data + i;

        sub_buffer++;
        buffer_index++;

        if (buffer_index >= 512) {
            fs_dump();
            *sub_buffer = *buffer;
        }
    }

    return 0;
}

/**
 * Writes buffer into a file
 * @return status code
 */
int fs_dump() {
    write_out(buffer, buffer_index); // TODO: Handle err
    buffer_index = 0;

    return 0;
}

/**
 * Cleanup
 * @return status code
 */
int fs_close() {
    if (buffer_index > 0) {
        fs_dump();
    }


    num_flights++;



    return 0;
}