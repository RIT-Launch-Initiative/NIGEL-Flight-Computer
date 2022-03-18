#ifndef RUNCAM_H
#define RUNCAM_H

#include <stdint.h>
#include <stdio.h>

typedef enum {
    RC_OK,
    RC_ERR
} rc_ret_t;

typdef enum {
    RC_READ_CAM_INFO,
    RC_CAM_CONTROL,
    RC_PRESS_FIVE,
    RC_RELEASE_FIVE,
    RC_HANDSHAKE_DISCONNECT,
    RC_REQUEST_ATTITUDE,
    RC_GET_SUB_SETTINGS,
    RC_READ_SETTING,
    RC_WRITE_SETTING,
    RC_FILL_SCREEN,
    RC_WRITE_CHAR,
    RC_WRITE_HORIZ_STR,
    RC_WRITE_VERT_STR,
    RC_WRITE_CHAR_AT,
} rc_cmd_t;

/**
 * Initialize the runcam module
 * @return RC_OK or RC_ERR
 */
rc_ret_t rc_init(void);

/**
 * Execute a command on the runcam
 * @param cmd The command to execute
 */
rc_ret_t rc_exec_cmd(rc_cmd_t cmd);

/**
 * CRC Checksum implementation
 * @param crc
 * @param a
 * @return checksum
 */
uint8_t rc_crc_checksum(uint8_t crc, unsigned char a);