/*
 * Control code for the high-G accelerometer
 * Contains interface intializer and wrappers for blocking HAL I2C I/O
 */


// Platform read/write using HAL and I2C bus 

int _platform_write(void *handle, uint8_t reg, const uint8_t *buf, uint16_t len) {
    return (int)HAL_I2C_Mem_Write(
			handle, H3LIS100DL_I2C_ADDRESS, reg, 1, buf, len, H3LIS100DL_TIMEOUT
	);  
}

int _platform_read(void *handle, uint8_t reg, uint8_t *buf, uint16_t len) {
    return (int)HAL_I2C_Mem_Read(
			handle, H3LIS100DL_I2C_ADDRESS, reg, 1, buf, len, H3LIS100DL_TIMEOUT
	);  
}


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
