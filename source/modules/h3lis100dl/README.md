H3LIS100DL driver provided by STMicroelectronics; see LICENSE.

# Implementation requirements
Define read/write:
```
/** Please note that is MANDATORY: return 0 -> no Error.**/
int32_t platform_write(void *handle, uint8_t Reg, const uint8_t *Bufp, uint16_t len)
int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp, uint16_t len)
```

Declare and initalize interface structure:

```
xxxxxxx_ctx_t dev_ctx; /** xxxxxxx is the used part number **/
dev_ctx.write_reg = platform_write;
dev_ctx.read_reg = platform_read;
```

Initalize the handle if necessary:
```
dev_ctx.handle = &platform_handle;
```

# Notes
- None
