// This code is untested

#include "h3lis100dl_reg.h"

#ifndef HIGHG_H
#define HIGHG_H

// timeout in ms
#define H3LIS100DL_I2C_TIMEOUT 100 
// SAO is pulled to VCC on the schematic
#define H3LIS100DL_I2C_ADDRESS 0x33U 

// xyz acceleration [m/s^2]
typedef struct { 
	float x;
	float y;
	float z;
} accel_t;

/**
 * @brief	Gets xyz acceleration and writes to struct
 *
 * @param	ctx		H3LIS100DLTR's interface struct
 * @param	dest	Acceleration struct to write to
 * @retval			0: success; -1: no new data; 1-3: I2C failure (HAL status)
 */
int highg_get_accel(stmdev_ctx_t* ctx, accel_t* dest);
#endif
