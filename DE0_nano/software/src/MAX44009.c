// Includes
#include "MAX44009.h"

alt_u8 MAX_getlum(alt_u32 clk_base, alt_u32 data_base, alt_u8 i2c_addr, double* data){
	
	alt_u8 read_data[2];
	bool ack;
	
	//start
	i2c_start(clk_base, data_base);
	
	// write device address
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x0);
	if(!ack){return -1;}
	
	// ask for temperature
	ack = i2c_write(clk_base, data_base, 0x03);
	if(!ack){return -1;}
	
	//restart
	i2c_start(clk_base, data_base);
	
	//read values
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x1);
	if(!ack){return -1;}
	
	// read response
	i2c_read(clk_base, data_base, &read_data[0], 0);
	
	//restart
	i2c_start(clk_base, data_base);
	
	// write device address
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x0);
	if(!ack){return -1;}
	
	// ask for temperature
	ack = i2c_write(clk_base, data_base, 0x04);
	if(!ack){return -1;}
	
	//restart
	i2c_start(clk_base, data_base);
	
	//read values
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x1);
	if(!ack){return -1;}
	
	// read response
	i2c_read(clk_base, data_base, &read_data[1], 0);
	
	//stop
	i2c_stop(clk_base, data_base);
	
	alt_u8 M = (read_data[1]&0x0F)|((read_data[1]<<4)&0xF0);
	alt_u8 E = (read_data[0]>>4)&0xF;	
	
	double val = 0.045*pow(2,E)*M;	
	*data = val;
	
	return (alt_u16)val;
	
	}
	