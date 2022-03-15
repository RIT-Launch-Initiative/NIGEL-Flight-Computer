#include "highg.h"

// Reads acceleration if new data available using interface struct pointer ctx
// Writes acceleration to acceleration struct pointed to by dest
int highg_get_accel(stmdev_ctx_t* ctx, accel_t* dest)
{
	int ret;
	h3lis100dl_reg_t reg;
	ret = h3lis100dl_status_reg_get(ctx, &reg.status_reg);
	
	if (ret) // unsuccessful read of status registers
	{ 
		return ret;
	}

	if (reg.status_reg.zyxda) // data available
	{ 
		// read acceleration registers
		int16_t val[] = {0, 0, 0};
		ret = h3lis100dl_acceleration_raw_get(ctx, val);

		if (ret) // unsuccessful read of acceleration registers
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
