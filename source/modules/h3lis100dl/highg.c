#include "highg.h"

// Platform read/write using HAL and I2C bus {

int32_t _platform_write(void *handle, uint8_t reg, const uint8_t *buf, uint16_t len) {
    return (int32_t)HAL_I2C_Mem_Write(
			handle, H3LIS100DL_I2C_ADDRESS, reg, 1, buf, len, H3LIS100DL_TIMEOUT
	);  
}

int32_t _platform_read(void *handle, uint8_t reg, uint8_t *buf, uint16_t len) {
    return (int32_t)HAL_I2C_Mem_Read(
			handle, H3LIS100DL_I2C_ADDRESS, reg, 1, buf, len, H3LIS100DL_TIMEOUT
	);  
}

//}

// Initalize and return interface struct

stmdev_ctx_t init_highg(void* handle) 
{
	stmdev_ctx_t ctx = 
	{
		.read_reg = _platform_read, 
		.write_reg = _platform_write, 
		.handle = handle
	};
	return ctx;
}

/** Puts acceleration into acceleration struct given pointed to by dest
 * Returns
 * 0: success
 * 1-3: read failure (see HAL status)
 * -1: No new data
 *  	Does not conflict with HAL statuses, which are all nonnegative
 */

int32_t highg_get_accel(stmdev_ctx_t* ctx, accel_t* dest)
{
	int32_t ret;
	h3lis100dl_reg_t reg;
	ret = h3lis100dl_status_reg_get(ctx, &reg.status_reg);
	
	if (ret) // unsuccessful read 
	{
		return ret;
	}

	if (reg.status_reg.zyxda) // data available
	{
		// get acceleration registers
		int16_t val[] = {0, 0, 0};
		ret = h3lis100dl_acceleration_raw_get(ctx, val);

		if (ret) // unsuccessful read
		{
			return ret; 
		}
		
		// convert return values to m/s^2
		// use library for raw -> miligee, then mulitply for miligee -> m/s^2
		dest->x = (float)h3lis100dl_from_fs100g_to_mg(val[0]) * 9.81e-3f;
		dest->y = (float)h3lis100dl_from_fs100g_to_mg(val[1]) * 9.81e-3f;
		dest->z = (float)h3lis100dl_from_fs100g_to_mg(val[2]) * 9.81e-3f;
		// this means a minimum resolution of ~0.01 m/s^2
	} 
	else
	{
		return -1;
	}

	return 0;
}
