/**
  ******************************************************************************
  * @file    h3lis100dl_reg.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          h3lis100dl_reg.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H3LIS100DL_REGS_H
#define H3LIS100DL_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup H3LIS100DL
  * @{
  *
  */



/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Customizable optional pointer **/
  void *handle;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */


/** @defgroup H3LIS100DL_Infos
  *  @{
  *
  */

/** I2C Device Address 8 bit format  if SA0=0 -> 0x31 if SA0=1 -> 0x33 **/
#define H3LIS100DL_I2C_ADD_L     0x31U
#define H3LIS100DL_I2C_ADD_H     0x33U


// timeout [ms] --- TODO: figure out what this should actually be
#define H3LIS100DL_TIMEOUT 100

/** Device Identification (Who am I) **/
#define H3LIS100DL_ID            0x32U

/**
  * @}
  *
  */

#define H3LIS100DL_WHO_AM_I                  0x0FU
#define H3LIS100DL_CTRL_REG1                 0x20U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xen                      : 1;
  uint8_t yen                      : 1;
  uint8_t zen                      : 1;
  uint8_t dr                       : 2;
  uint8_t pm                       : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t pm                       : 3;
  uint8_t dr                       : 2;
  uint8_t zen                      : 1;
  uint8_t yen                      : 1;
  uint8_t xen                      : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_ctrl_reg1_t;

#define H3LIS100DL_CTRL_REG2                 0x21U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t hpcf                     : 2;
  uint8_t hpen                     : 2;
  uint8_t fds                      : 1;
  uint8_t hpm                      : 2;
  uint8_t boot                     : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot                     : 1;
  uint8_t hpm                      : 2;
  uint8_t fds                      : 1;
  uint8_t hpen                     : 2;
  uint8_t hpcf                     : 2;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_ctrl_reg2_t;

#define H3LIS100DL_CTRL_REG3                 0x22U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t i1_cfg                   : 2;
  uint8_t lir1                     : 1;
  uint8_t i2_cfg                   : 2;
  uint8_t lir2                     : 1;
  uint8_t pp_od                    : 1;
  uint8_t ihl                      : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t ihl                      : 1;
  uint8_t pp_od                    : 1;
  uint8_t lir2                     : 1;
  uint8_t i2_cfg                   : 2;
  uint8_t lir1                     : 1;
  uint8_t i1_cfg                   : 2;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_ctrl_reg3_t;

#define H3LIS100DL_CTRL_REG4                 0x23U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sim                      : 1;
  uint8_t not_used_01              : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t sim                      : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_ctrl_reg4_t;

#define H3LIS100DL_CTRL_REG5                 0x24U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t turnon                   : 2;
  uint8_t not_used_01              : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t turnon                   : 2;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_ctrl_reg5_t;

#define H3LIS100DL_HP_FILTER_RESET           0x25U
#define H3LIS100DL_REFERENCE                 0x26U
#define H3LIS100DL_STATUS_REG                0x27U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xda                      : 1;
  uint8_t yda                      : 1;
  uint8_t zda                      : 1;
  uint8_t zyxda                    : 1;
  uint8_t _xor                     : 1;
  uint8_t yor                      : 1;
  uint8_t zor                      : 1;
  uint8_t zyxor                    : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t zyxor                    : 1;
  uint8_t zor                      : 1;
  uint8_t yor                      : 1;
  uint8_t _xor                     : 1;
  uint8_t zyxda                    : 1;
  uint8_t zda                      : 1;
  uint8_t yda                      : 1;
  uint8_t xda                      : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_status_reg_t;

#define H3LIS100DL_OUT_X                     0x29U
#define H3LIS100DL_OUT_Y                     0x2BU
#define H3LIS100DL_OUT_Z                     0x2DU
#define H3LIS100DL_INT1_CFG                  0x30U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xlie                     : 1;
  uint8_t xhie                     : 1;
  uint8_t ylie                     : 1;
  uint8_t yhie                     : 1;
  uint8_t zlie                     : 1;
  uint8_t zhie                     : 1;
  uint8_t not_used_01              : 1;
  uint8_t aoi                      : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t aoi                      : 1;
  uint8_t not_used_01              : 1;
  uint8_t zhie                     : 1;
  uint8_t zlie                     : 1;
  uint8_t yhie                     : 1;
  uint8_t ylie                     : 1;
  uint8_t xhie                     : 1;
  uint8_t xlie                     : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int1_cfg_t;

#define H3LIS100DL_INT1_SRC                  0x31U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xl                       : 1;
  uint8_t xh                       : 1;
  uint8_t yl                       : 1;
  uint8_t yh                       : 1;
  uint8_t zl                       : 1;
  uint8_t zh                       : 1;
  uint8_t ia                       : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t ia                       : 1;
  uint8_t zh                       : 1;
  uint8_t zl                       : 1;
  uint8_t yh                       : 1;
  uint8_t yl                       : 1;
  uint8_t xh                       : 1;
  uint8_t xl                       : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int1_src_t;

#define H3LIS100DL_INT1_THS                  0x32U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ths                      : 7;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t ths                      : 7;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int1_ths_t;

#define H3LIS100DL_INT1_DURATION             0x33U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t d                        : 7;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t d                        : 7;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int1_duration_t;

#define H3LIS100DL_INT2_CFG                  0x34U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xlie                     : 1;
  uint8_t xhie                     : 1;
  uint8_t ylie                     : 1;
  uint8_t yhie                     : 1;
  uint8_t zlie                     : 1;
  uint8_t zhie                     : 1;
  uint8_t not_used_01              : 1;
  uint8_t aoi                      : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t aoi                      : 1;
  uint8_t not_used_01              : 1;
  uint8_t zhie                     : 1;
  uint8_t zlie                     : 1;
  uint8_t yhie                     : 1;
  uint8_t ylie                     : 1;
  uint8_t xhie                     : 1;
  uint8_t xlie                     : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int2_cfg_t;

#define H3LIS100DL_INT2_SRC                  0x35U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xl                       : 1;
  uint8_t xh                       : 1;
  uint8_t yl                       : 1;
  uint8_t yh                       : 1;
  uint8_t zl                       : 1;
  uint8_t zh                       : 1;
  uint8_t ia                       : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t ia                       : 1;
  uint8_t zh                       : 1;
  uint8_t zl                       : 1;
  uint8_t yh                       : 1;
  uint8_t yl                       : 1;
  uint8_t xh                       : 1;
  uint8_t xl                       : 1;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int2_src_t;

#define H3LIS100DL_INT2_THS                  0x36U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ths                      : 7;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t ths                      : 7;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int2_ths_t;

#define H3LIS100DL_INT2_DURATION             0x37U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t d                        : 7;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t d                        : 7;
#endif /* DRV_BYTE_ORDER */
} h3lis100dl_int2_duration_t;

/**
  * @defgroup H3LIS100DL_Register_Union
  * @brief    This union group all the registers having a bit-field
  *           description.
  *           This union is useful but it's not needed by the driver.
  *
  *           REMOVING this union you are compliant with:
  *           MISRA-C 2012 [Rule 19.2] -> " Union are not allowed "
  *
  * @{
  *
  */
typedef union
{
  h3lis100dl_ctrl_reg1_t                     ctrl_reg1;
  h3lis100dl_ctrl_reg2_t                     ctrl_reg2;
  h3lis100dl_ctrl_reg3_t                     ctrl_reg3;
  h3lis100dl_ctrl_reg4_t                     ctrl_reg4;
  h3lis100dl_ctrl_reg5_t                     ctrl_reg5;
  h3lis100dl_status_reg_t                    status_reg;
  h3lis100dl_int1_cfg_t                      int1_cfg;
  h3lis100dl_int1_src_t                      int1_src;
  h3lis100dl_int1_ths_t                      int1_ths;
  h3lis100dl_int1_duration_t                 int1_duration;
  h3lis100dl_int2_cfg_t                      int2_cfg;
  h3lis100dl_int2_src_t                      int2_src;
  h3lis100dl_int2_ths_t                      int2_ths;
  h3lis100dl_int2_duration_t                 int2_duration;
  bitwise_t                                 bitwise;
  uint8_t                                   byte;
} h3lis100dl_reg_t;

/**
  * @}
  *
  */

int32_t platform_write(void* handle, uint8_t Reg, 
					   const uint8_t* Bufp, 
					   uint16_t len);
int32_t platform_read(void* handle, uint8_t	Reg, 
					  uint8_t* Bufp, 
					  uint16_t len);

int32_t h3lis100dl_read_reg(stmdev_ctx_t *ctx, uint8_t reg,
                            uint8_t *data,
                            uint16_t len);
int32_t h3lis100dl_write_reg(stmdev_ctx_t *ctx, uint8_t reg,
                             uint8_t *data,
                             uint16_t len);

float_t h3lis100dl_from_fs100g_to_mg(int8_t lsb);

int32_t h3lis100dl_axis_x_data_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_axis_x_data_get(stmdev_ctx_t *ctx, uint8_t *val);

int32_t h3lis100dl_axis_y_data_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_axis_y_data_get(stmdev_ctx_t *ctx, uint8_t *val);

int32_t h3lis100dl_axis_z_data_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_axis_z_data_get(stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  H3LIS100DL_ODR_OFF   = 0x00,
  H3LIS100DL_ODR_Hz5   = 0x02,
  H3LIS100DL_ODR_1Hz   = 0x03,
  H3LIS100DL_ODR_2Hz   = 0x04,
  H3LIS100DL_ODR_5Hz   = 0x05,
  H3LIS100DL_ODR_10Hz  = 0x06,
  H3LIS100DL_ODR_50Hz  = 0x01,
  H3LIS100DL_ODR_100Hz = 0x11,
  H3LIS100DL_ODR_400Hz = 0x21,
} h3lis100dl_dr_t;
int32_t h3lis100dl_data_rate_set(stmdev_ctx_t *ctx,
                                 h3lis100dl_dr_t val);
int32_t h3lis100dl_data_rate_get(stmdev_ctx_t *ctx,
                                 h3lis100dl_dr_t *val);

typedef enum
{
  H3LIS100DL_NORMAL_MODE      = 0,
  H3LIS100DL_REF_MODE_ENABLE  = 1,
} h3lis100dl_hpm_t;
int32_t h3lis100dl_reference_mode_set(stmdev_ctx_t *ctx,
                                      h3lis100dl_hpm_t val);
int32_t h3lis100dl_reference_mode_get(stmdev_ctx_t *ctx,
                                      h3lis100dl_hpm_t *val);

int32_t h3lis100dl_status_reg_get(stmdev_ctx_t *ctx,
                                  h3lis100dl_status_reg_t *val);

int32_t h3lis100dl_flag_data_ready_get(stmdev_ctx_t *ctx,
                                       uint8_t *val);

int32_t h3lis100dl_acceleration_raw_get(stmdev_ctx_t *ctx,
                                        int16_t *val);

int32_t h3lis100dl_device_id_get(stmdev_ctx_t *ctx, uint8_t *buff);

int32_t h3lis100dl_boot_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_boot_get(stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  H3LIS100DL_CUT_OFF_8Hz   = 0,
  H3LIS100DL_CUT_OFF_16Hz  = 1,
  H3LIS100DL_CUT_OFF_32Hz  = 2,
  H3LIS100DL_CUT_OFF_64Hz  = 3,
} h3lis100dl_hpcf_t;
int32_t h3lis100dl_hp_bandwidth_set(stmdev_ctx_t *ctx,
                                    h3lis100dl_hpcf_t val);
int32_t h3lis100dl_hp_bandwidth_get(stmdev_ctx_t *ctx,
                                    h3lis100dl_hpcf_t *val);

typedef enum
{
  H3LIS100DL_HP_DISABLE            = 0,
  H3LIS100DL_HP_ON_OUT             = 4,
  H3LIS100DL_HP_ON_INT1            = 1,
  H3LIS100DL_HP_ON_INT2            = 2,
  H3LIS100DL_HP_ON_INT1_INT2       = 3,
  H3LIS100DL_HP_ON_INT1_INT2_OUT   = 7,
  H3LIS100DL_HP_ON_INT2_OUT        = 6,
  H3LIS100DL_HP_ON_INT1_OUT        = 5,
} h3lis100dl_hpen_t;
int32_t h3lis100dl_hp_path_set(stmdev_ctx_t *ctx,
                               h3lis100dl_hpen_t val);
int32_t h3lis100dl_hp_path_get(stmdev_ctx_t *ctx,
                               h3lis100dl_hpen_t *val);

int32_t h3lis100dl_hp_reset_get(stmdev_ctx_t *ctx);

int32_t h3lis100dl_hp_reference_value_set(stmdev_ctx_t *ctx,
                                          uint8_t val);
int32_t h3lis100dl_hp_reference_value_get(stmdev_ctx_t *ctx,
                                          uint8_t *val);

typedef enum
{
  H3LIS100DL_SPI_4_WIRE  = 0,
  H3LIS100DL_SPI_3_WIRE  = 1,
} h3lis100dl_sim_t;
int32_t h3lis100dl_spi_mode_set(stmdev_ctx_t *ctx,
                                h3lis100dl_sim_t val);
int32_t h3lis100dl_spi_mode_get(stmdev_ctx_t *ctx,
                                h3lis100dl_sim_t *val);

typedef enum
{
  H3LIS100DL_PAD1_INT1_SRC           = 0,
  H3LIS100DL_PAD1_INT1_OR_INT2_SRC   = 1,
  H3LIS100DL_PAD1_DRDY               = 2,
  H3LIS100DL_PAD1_BOOT               = 3,
} h3lis100dl_i1_cfg_t;
int32_t h3lis100dl_pin_int1_route_set(stmdev_ctx_t *ctx,
                                      h3lis100dl_i1_cfg_t val);
int32_t h3lis100dl_pin_int1_route_get(stmdev_ctx_t *ctx,
                                      h3lis100dl_i1_cfg_t *val);

typedef enum
{
  H3LIS100DL_INT1_PULSED   = 0,
  H3LIS100DL_INT1_LATCHED  = 1,
} h3lis100dl_lir1_t;
int32_t h3lis100dl_int1_notification_set(stmdev_ctx_t *ctx,
                                         h3lis100dl_lir1_t val);
int32_t h3lis100dl_int1_notification_get(stmdev_ctx_t *ctx,
                                         h3lis100dl_lir1_t *val);

typedef enum
{
  H3LIS100DL_PAD2_INT2_SRC           = 0,
  H3LIS100DL_PAD2_INT1_OR_INT2_SRC   = 1,
  H3LIS100DL_PAD2_DRDY               = 2,
  H3LIS100DL_PAD2_BOOT               = 3,
} h3lis100dl_i2_cfg_t;
int32_t h3lis100dl_pin_int2_route_set(stmdev_ctx_t *ctx,
                                      h3lis100dl_i2_cfg_t val);
int32_t h3lis100dl_pin_int2_route_get(stmdev_ctx_t *ctx,
                                      h3lis100dl_i2_cfg_t *val);

typedef enum
{
  H3LIS100DL_INT2_PULSED   = 0,
  H3LIS100DL_INT2_LATCHED  = 1,
} h3lis100dl_lir2_t;
int32_t h3lis100dl_int2_notification_set(stmdev_ctx_t *ctx,
                                         h3lis100dl_lir2_t val);
int32_t h3lis100dl_int2_notification_get(stmdev_ctx_t *ctx,
                                         h3lis100dl_lir2_t *val);

typedef enum
{
  H3LIS100DL_PUSH_PULL   = 0,
  H3LIS100DL_OPEN_DRAIN  = 1,
} h3lis100dl_pp_od_t;
int32_t h3lis100dl_pin_mode_set(stmdev_ctx_t *ctx,
                                h3lis100dl_pp_od_t val);
int32_t h3lis100dl_pin_mode_get(stmdev_ctx_t *ctx,
                                h3lis100dl_pp_od_t *val);

typedef enum
{
  H3LIS100DL_ACTIVE_HIGH  = 0,
  H3LIS100DL_ACTIVE_LOW   = 1,
} h3lis100dl_ihl_t;
int32_t h3lis100dl_pin_polarity_set(stmdev_ctx_t *ctx,
                                    h3lis100dl_ihl_t val);
int32_t h3lis100dl_pin_polarity_get(stmdev_ctx_t *ctx,
                                    h3lis100dl_ihl_t *val);

typedef struct
{
  uint8_t int1_xlie             : 1;
  uint8_t int1_xhie             : 1;
  uint8_t int1_ylie             : 1;
  uint8_t int1_yhie             : 1;
  uint8_t int1_zlie             : 1;
  uint8_t int1_zhie             : 1;
} int1_on_th_conf_t;
int32_t h3lis100dl_int1_on_threshold_conf_set(stmdev_ctx_t *ctx,
                                              int1_on_th_conf_t val);
int32_t h3lis100dl_int1_on_threshold_conf_get(stmdev_ctx_t *ctx,
                                              int1_on_th_conf_t *val);

typedef enum
{
  H3LIS100DL_INT1_ON_THRESHOLD_OR   = 0,
  H3LIS100DL_INT1_ON_THRESHOLD_AND  = 1,
} h3lis100dl_int1_aoi_t;
int32_t h3lis100dl_int1_on_threshold_mode_set(stmdev_ctx_t *ctx,
                                              h3lis100dl_int1_aoi_t val);
int32_t h3lis100dl_int1_on_threshold_mode_get(stmdev_ctx_t *ctx,
                                              h3lis100dl_int1_aoi_t *val);

int32_t h3lis100dl_int1_src_get(stmdev_ctx_t *ctx,
                                h3lis100dl_int1_src_t *val);

int32_t h3lis100dl_int1_treshold_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_int1_treshold_get(stmdev_ctx_t *ctx, uint8_t *val);

int32_t h3lis100dl_int1_dur_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_int1_dur_get(stmdev_ctx_t *ctx, uint8_t *val);

typedef struct
{
  uint8_t int2_xlie             : 1;
  uint8_t int2_xhie             : 1;
  uint8_t int2_ylie             : 1;
  uint8_t int2_yhie             : 1;
  uint8_t int2_zlie             : 1;
  uint8_t int2_zhie             : 1;
} int2_on_th_conf_t;
int32_t h3lis100dl_int2_on_threshold_conf_set(stmdev_ctx_t *ctx,
                                              int2_on_th_conf_t val);
int32_t h3lis100dl_int2_on_threshold_conf_get(stmdev_ctx_t *ctx,
                                              int2_on_th_conf_t *val);

typedef enum
{
  H3LIS100DL_INT2_ON_THRESHOLD_OR   = 0,
  H3LIS100DL_INT2_ON_THRESHOLD_AND  = 1,
} h3lis100dl_int2_aoi_t;
int32_t h3lis100dl_int2_on_threshold_mode_set(stmdev_ctx_t *ctx,
                                              h3lis100dl_int2_aoi_t val);
int32_t h3lis100dl_int2_on_threshold_mode_get(stmdev_ctx_t *ctx,
                                              h3lis100dl_int2_aoi_t *val);

int32_t h3lis100dl_int2_src_get(stmdev_ctx_t *ctx,
                                h3lis100dl_int2_src_t *val);

int32_t h3lis100dl_int2_treshold_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_int2_treshold_get(stmdev_ctx_t *ctx, uint8_t *val);

int32_t h3lis100dl_int2_dur_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_int2_dur_get(stmdev_ctx_t *ctx, uint8_t *val);

int32_t h3lis100dl_wkup_to_sleep_set(stmdev_ctx_t *ctx, uint8_t val);
int32_t h3lis100dl_wkup_to_sleep_get(stmdev_ctx_t *ctx, uint8_t *val);

/**
  *@}
  *
  */

#ifdef __cplusplus
}
#endif

#endif /* H3LIS100DL_REGS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/