#ifndef __LM75_H__
#define __LM75_H__

#include "I2C.h"

alt_u8 LM75_getTemp(alt_u32 /*clk_base*/, alt_u32 /*data_base*/,  alt_u8 /*i2c_addr*/, double* /*data*/);

#endif