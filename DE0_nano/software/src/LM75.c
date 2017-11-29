// Includes
#include "LM75.h"

alt_u8 LM75_getTemp(alt_u32 clk_base, alt_u32 data_base, alt_u8 i2c_addr, double* data){
	
	alt_u8 read_data[2];
	bool ack;
	
	//start
	i2c_start(clk_base, data_base);
	
	// write device address
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x0);
	if(!ack){return -1;}
	
	// ask for temperature
	ack = i2c_write(clk_base, data_base, 0);
	if(!ack){return -1;}
	
	//restart
	i2c_start(clk_base, data_base);
	
	//read values
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x1);
	if(!ack){return -1;}
	
	// read MSByte response
	i2c_read(clk_base, data_base, &read_data[0], 1);
	
	// read LSByte response
	i2c_read(clk_base, data_base, &read_data[1], 0);
	
	//stop
	i2c_stop(clk_base, data_base);
	
	
	double val = 0.5*(double)(((read_data[1]&0x80)>>7)|(read_data[0]<<1));
	*data = val;
	
	
	return 0;
	
	}