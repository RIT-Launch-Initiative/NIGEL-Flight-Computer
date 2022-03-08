#include "high-g.h"

int32_t highg_init(void* handle)
{
	highg_ctx.write_reg = platform_write;
	highg_ctx.read_reg = platform_read;
	highg_ctx.handle = handle;

	return 0; // will return errors later
}

int32_t highg_get_accel(stmdev_ctx_t* ctx, accel_t* accel);
{
	int16_t val[] = {0 0 0};
	ret = h3lis100dl_acceleration_raw_get(ctx, val);
	
	// convert return values to m/s^2
	// use library for raw -> mg, then divide for mg -> m/s^2
	accel->x = (float)h3lis100dl_from_fs100g_to_mg(val[0]) / 9.81e-3f;
	accel->y = (float)h3lis100dl_from_fs100g_to_mg(val[1]) / 9.81e-3f;
	accel->z = (float)h3lis100dl_from_fs100g_to_mg(val[2]) / 9.81e-3f;
	
	return ret;	
}
