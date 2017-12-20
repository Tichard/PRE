#ifndef __ADC128S022_H__
#define __ADC128S022_H__

// Includes
#include "alt_types.h"

#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"


double ADC_getData(alt_u32 /*base*/, alt_u32 /*slave*/, alt_u8 /*IN*/);

#endif