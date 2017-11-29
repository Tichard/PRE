#ifndef __ADXL345_H__
#define __ADXL345_H__

// Includes
#include "I2C.h"
#include "accelerometer_adxl345.h"

alt_u8 ADXL_start(alt_u32 /*clk_base*/, alt_u32 /*data_base*/, alt_u8 /*i2c_addr*/);
alt_u8 ADXL_setRange(alt_u32 /*clk_base*/, alt_u32 /*data_base*/, alt_u8 /*i2c_addr*/, alt_u8 /*range*/);
alt_u8 ADXL_getAxis(alt_u32 /*clk_base*/, alt_u32 /*data_base*/, alt_u8 /*i2c_addr*/, double* /*values*/);


#endif