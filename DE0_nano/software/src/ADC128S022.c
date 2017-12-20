#include "ADC128S022.h"


double ADC_getData(alt_u32 base, alt_u32 slave, alt_u8 IN){
	
	alt_u8 selectIn = (IN<<3)&0x38; 
	
	alt_u8 * write_data = &selectIn;
	alt_u8 read_data[2];
	
	int n = alt_avalon_spi_command(base, slave, sizeof(alt_u8), write_data, 12, read_data, 0);
	if(n>0)
	{
		alt_u16 returnVal = read_data[1]<<8 | read_data[0]; 
		return (double)(returnVal/40.95);
	}
	else return (-1);
}