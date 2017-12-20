// Includes
#include "ADXL345.h"

alt_u8 ADXL_start(alt_u32 clk_base, alt_u32 data_base, alt_u8 i2c_addr){
	
	bool ack;
	
	//start
	i2c_start(clk_base, data_base);
	
	// write device address
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x0);
	if(!ack){return -1;}
	
	// ask for data format register
	ack = i2c_write(clk_base, data_base, ADXL345_REG_POWER_CTL);
	if(!ack){return -1;}
	
	//write format
	ack = i2c_write(clk_base, data_base, XL345_MEASURE);
	if(!ack){return -1;}
	
	//stop
	i2c_stop(clk_base, data_base);
	
	return 0;
	
	
	
}

alt_u8 ADXL_setRange(alt_u32 clk_base, alt_u32 data_base, alt_u8 i2c_addr, alt_u8 range){
	
	alt_u8 format;
	bool ack;
	switch(range){
		case 2 : format = XL345_RANGE_2G; break;
		case 4 : format = XL345_RANGE_4G; break;
		case 8 : format = XL345_RANGE_8G; break;
		case 16 : format = XL345_RANGE_16G; break;
		default : format = XL345_RANGE_2G; break;
	}	
	
	//start
	i2c_start(clk_base, data_base);
	
	// write device address
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x0);
	if(!ack){return -1;}
	
	// ask for data format register
	ack = i2c_write(clk_base, data_base, ADXL345_REG_DATA_FORMAT);
	if(!ack){return -1;}
	
	//write format
	ack = i2c_write(clk_base, data_base, format);
	if(!ack){return -1;}
	
	//stop
	i2c_stop(clk_base, data_base);
	
	return 0;
	
	}


alt_u8 ADXL_getAxis(alt_u32 clk_base, alt_u32 data_base, alt_u8 i2c_addr, double* values){
	
	alt_u8 read_data[6];
	bool ack;
	
	//start
	i2c_start(clk_base, data_base);
	
	// write device address
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x0);
	if(!ack){return -1;}
	
	// ask for axis value
	ack = i2c_write(clk_base, data_base, ADXL345_REG_DATAX0);
	if(!ack){return -1;}
	
	//restart
	i2c_start(clk_base, data_base);
	
	//read values
	ack = i2c_write(clk_base, data_base, (i2c_addr<<1)|0x1);
	if(!ack){return -1;}
	
	// read response
	i2c_read(clk_base, data_base, &read_data[5], 1);
	
	// read response
	i2c_read(clk_base, data_base, &read_data[4], 1);
	
	// read response
	i2c_read(clk_base, data_base, &read_data[3], 1);
	
	// read response
	i2c_read(clk_base, data_base, &read_data[2], 1);
	
	// read response
	i2c_read(clk_base, data_base, &read_data[1], 1);
	
	// read response
	i2c_read(clk_base, data_base, &read_data[0], 0);
	
	//stop
	i2c_stop(clk_base, data_base);
	
	values[0] = (alt_16)((read_data[4]<<8)|read_data[5]);
	
	values[1] = (alt_16)((read_data[2]<<8)|read_data[3]);
	
	values[2] = (alt_16)((read_data[0]<<8)|read_data[1]);
	
	return 0;
	
	}
	
	