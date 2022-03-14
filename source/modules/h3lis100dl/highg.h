#include "h3lis100dl_reg.h"

#ifndef HIGHG
#define HIGHG

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

// Initalize and return interface struct
stmdev_ctx_t init_highg(void* handle);

/** Puts acceleration into acceleration struct given pointed to by dest
 * Returns
 * 0: success
 * 1-3: read failure (see HAL status)
 * -1: No new data
 *  	Does not conflict with HAL statuses, which are all nonnegative
 */
int32_t highg_get_accel(stmdev_ctx_t* ctx, accel_t* dest);
#endif
