
#include <stdio.h>
#include <string.h>
#include "main.h"

#define ms_sleep(delay)		(usleep(1000*delay))
#define sec_sleep(delay)	(ms_sleep(1000*delay))

static alt_u8 frame_id;

int main ()
{
	
	
	// configure ADXL
	if(ADXL_setRange(I2C_SCL_BASE, I2C_SDA_BASE, addrADXL, 4)==-1){return -1;}
	
	if(ADXL_start(I2C_SCL_BASE, I2C_SDA_BASE, addrADXL)==-1){return -1;}
	
	
	frame_id = 0;
	
	double pot[2];
	double accel[3];
	double lux;
	double temp;
	
	alt_u8 data[3];
	
	
	FILE* fd = fopen ("/dev/xbee_uart", "w"); //Open file for writing
	// say Hi to coordinator
	XBeeDataSend(fd, 0, data, 0);
	XBeeDataSend(fd, 0, data, 0);
	
	//send P1 ADC unit - 1
	XBeeUnitSend(fd, 1, "%  ");
	
	//send P2 ADC unit - 2
	XBeeUnitSend(fd, 2, "%  ");
	
	//send accel unit - X : 3/ Y : 4 / Z : 5
	XBeeUnitSend(fd, 3, "g_X");	
	XBeeUnitSend(fd, 4, "g_Y");
	XBeeUnitSend(fd, 5, "g_Z");
	
	//send lux unit - 6
	XBeeUnitSend(fd, 6, "lux");
	
	//send Temp unit - 7
	XBeeUnitSend(fd, 7, "C  ");
	
	while(fd)
	{
		//ADC
		pot[0] = ADC_getData(ADC_SPI_INT_BASE, 0, 0); // 0 to 100 *10 (10bits)
		data[0] = (alt_u8)((alt_32)(pot[0]*10)&0xFF);
		data[1] = (alt_u8)(((alt_32)(pot[0]*10)>>8)&0xFF);
		XBeeDataSend(fd, 1, data, 2);
		
		pot[1] = ADC_getData(ADC_SPI_INT_BASE, 0, 1); // 0 to 100 *10 (10bits)
		data[0] = (alt_u8)((alt_32)(pot[1]*10)&0xFF);
		data[1] = (alt_u8)(((alt_32)(pot[1]*10)>>8)&0xFF);
		XBeeDataSend(fd, 2, data, 2);
		
		// accel
		ADXL_getAxis(I2C_SCL_BASE, I2C_SDA_BASE, addrADXL, accel); // -2 to 2 -ish... *10 (5bits) each
		data[0] = (alt_u8)(accel[0]/12.8);
		XBeeDataSend(fd, 3, data, 1);
		data[0] = (alt_u8)(accel[1]/12.8);
		XBeeDataSend(fd, 4, data, 1);
		data[0] = (alt_u8)(accel[2]/12.8);
		XBeeDataSend(fd, 5, data, 1);
		
		// lux
		MAX_getlum(I2C_SCL_BASE, I2C_EXT_SDA_BASE, addrMAX, &lux); //0.045 to 188000 *10 (21bits)
		data[0] = (alt_u8)((alt_32)(lux*10)&0xFF);
		data[1] = (alt_u8)(((alt_32)(lux*10)>>8)&0xFF);
		data[2] = (alt_u8)(((alt_32)(lux*10)>>16)&0xFF);
		XBeeDataSend(fd, 6, data, 3);
		
		//temp
		LM75_getTemp(I2C_SCL_BASE, I2C_EXT_SDA_BASE, addrLM75, &temp); // -55 to 125 *10 
		data[0] = (alt_u8)((alt_32)(temp*10)&0xFF);
		data[1] = (alt_u8)(((alt_32)(temp*10)>>8)&0xFF);
		XBeeDataSend(fd, 7, data, 2);
	}
	
	fclose(fd);
	
	
	
return 0;
}

alt_u8 XBeeDataSend(FILE* fd, alt_u8 id_capteur, alt_u8* data, int data_size)
// send a data
{
	int i;
	int size = data_size + 16;
	alt_u8 msg[size];
	
	// frame type
	msg[0] = 0x10;
	
	// ID
	msg[1] = frame_id++;
	if(frame_id >= 255){frame_id=0;}
	// 64-bits Destination address
	msg[2] = 0;
	msg[3] = 0;
	msg[4] = 0;
	msg[5] = 0;
	msg[6] = 0;
	msg[7] = 0;
	msg[8] = 0;
	msg[9] = 0;
	// 16-bits Destination Network address
	msg[10]  = 0;
	msg[11] = 0;
	// Broadcast radius
	msg[12] = 0x00 ;
	// options
	msg[13] = 0x00 ;
	
	
	// ID capteur
	msg[14] = id_capteur ;
	
	// data transmitting
	msg[15] = 0x00 ;
	
	// data
	for( i = 0; i<data_size; i++)
	{msg[16+i] = data[i];}	
		
	// create arrays
	alt_u8 write_buf[size + 4];
	
	// create buffer
	write_buf[0] = 0x7E; // start
	write_buf[1] = size>>8; // MSB size
	write_buf[2] = size; // LSB size
	
	// recopy msg into buffer
	for(i = 0; i < size; i++)
	{write_buf[3+i] = msg[i];}
	
	write_buf[3+size] = checksum(msg, size ); // checksum	
	
	int n = fwrite(write_buf, sizeof(alt_u8), sizeof write_buf, fd);
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	
	return 0;
		
}


alt_u8 XBeeUnitSend(FILE* fd, alt_u8 id_capteur, char* unit)
// send an unit
{
	int i;
	int unit_size = strlen(unit);
	int size = unit_size + 16;
	
	alt_u8 msg[size];	

	// frame type
	msg[0] = 0x10;
	
	// ID
	msg[1] = frame_id++;
	if(frame_id >= 255){frame_id=0;}
	// 64-bits Destination address
	msg[2] = 0;
	msg[3] = 0;
	msg[4] = 0;
	msg[5] = 0;
	msg[6] = 0;
	msg[7] = 0;
	msg[8] = 0;
	msg[9] = 0;
	// 16-bits Destination Network address
	msg[10]  = 0;
	msg[11] = 0;
	// Broadcast radius
	msg[12] = 0x00 ;
	// options
	msg[13] = 0x00 ;
	
	
	// ID capteur
	msg[14] = id_capteur ;
	
	// Unit transmitting
	msg[15] = 0xFF ;
	
	// data
	for( i = 0; i<unit_size; i++)
	{msg[16+i] = (alt_u8)unit[i];}	
		
	// create arrays
	alt_u8 write_buf[size + 4];
	
	// create buffer
	write_buf[0] = 0x7E; // start
	write_buf[1] = size>>8; // MSB size
	write_buf[2] = size; // LSB size
	
	// recopy msg into buffer
	for(i = 0; i < size; i++)
	{write_buf[3+i] = msg[i];}
	
	write_buf[3+size] = checksum(msg, size ); // checksum	
	
	int n = fwrite(write_buf, sizeof(alt_u8), sizeof write_buf, fd);
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	
	return 0;
		
}


alt_u8 checksum(alt_u8* frame, unsigned long size)
// computes the checksum of the given frame
{
	int i;
	alt_u8 sum = 0;
	
	for(i = 0; i < size; i++)
	{
		sum += frame[i];
	}
	
	return 0xFF - (sum & 0xFF);
}