#include "h3lis100dl.h"

const stmdev_ctx_t highg_ctx;

// xyz acceleration [m/s^2]
typedef struct {
	float x;
	float y;
	float z;
} accel_t;

// for now, just initalizes highg_ctx
int32_t highg_init(void* handle);

// gets xyz and converts to accel_t
accel_t highg_get_accel(stmdev_ctx_t* ctx);
