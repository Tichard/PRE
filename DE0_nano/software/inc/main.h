#ifndef __MAIN_H__
#define __MAIN_H__

// Includes
#include "alt_types.h"
#include "terasic_includes.h"

#include "ADC128S022.h"
#include "ADXL345.h"
#include "MAX44009.h"
#include "LM75.h"

#define addrADXL 	0x1D
#define addrMAX 	0x4A
#define addrLM75 	0x48

alt_u8 XBeeDataSend(FILE* /*fd*/, alt_u8 /*id_capteur*/, alt_u8* /*data*/, int /*data_size*/);
alt_u8 XBeeUnitSend(FILE* /*fd*/, alt_u8 /*id_capteur*/, char* /*unit*/);
alt_u8 checksum(alt_u8* /*frame*/, unsigned long /*size*/);

#endif