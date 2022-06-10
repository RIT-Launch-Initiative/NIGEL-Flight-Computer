#include <stddef.h>
#include "fs.h"
#include "hashmap.h"

#define FILE_LIMIT 5 // TODO: Change this :)
#define DESCRIPTOR_PAGE 0

#ifndef FS_PAGE_SIZE
#define FS_PAGE_SIZE 4096
#endif

#define FS_BUFF_SIZE 512

static uint32_t *flights;
static uint32_t *buffer;
static uint8_t num_writes_page = 0;
static uint32_t num_flights = 0;
static uint32_t num_pages = 1;
static uint32_t buffer_index = 0;
static size_t current_flight_len = -1;

static uint32_t (*read_out) (uint8_t* buff, size_t len);
static uint32_t (*write_out) (uint32_t page_num, uint32_t* buff, size_t len);

/**
 * Initialize the fs
 * @return status code
 */
int fs_init(uint32_t (*read_fun) (uint8_t* buff, size_t len), uint32_t (*write_fun) (uint32_t page_num, uint32_t *buff, size_t len)) {
    read_out = read_fun;
    write_out = write_fun;

    current_flight_len++;

    return 0;
}

int fs_read(uint32_t flight_num) {
    if (flight_num > num_flights) {
        return 1;
    }

    uint32_t *start_flight = flights + (num_flights - 1);
    uint32_t *end_flight = flights + num_flights;
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
int fs_write(uint32_t *data, size_t len) {
    uint32_t *sub_buffer = buffer + buffer_index;

    for (int i = 0; i < len; i++) {
        sub_buffer = data + i;

        sub_buffer++;
        buffer_index++;
        current_flight_len++;

        if (buffer_index >= FS_BUFF_SIZE) {
            fs_dump();
            *sub_buffer = *buffer;
            buffer_index = 0;
        }
    }

    return 0;
}

/**
 * Writes buffer into a file
 * @return status code
 */
int fs_dump() {
    write_out(num_pages, buffer, buffer_index); // TODO: Handle err
    buffer_index = 0;

    num_writes_page++;

    if (num_writes_page >= (FS_PAGE_SIZE / FS_BUFF_SIZE)) {
        num_writes_page = 0;
        num_pages++;
    }

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