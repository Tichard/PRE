/*----------------------------------TEST.C----------------------------------*/
/*
 *> [File Name] test.c
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] alpha
 *> [Author] Richard
 *> [Language] C
 *> [Description] ZIGBEE API : 
 *> XBee test module
 */

#include "zigbee.h"

int main(void)
// main function for coordinator mode
{	
	
	int fd = serial_open("/dev/ttyUSB0",9600);
	
	
	double pot[2];
	double accel[3];
	double lux;
	double temp;
	
	uint8_t data[3];
	
	
	// say Hi to coordinator
	XBeeDataSend(fd, 0, data, 0);
	XBeeDataSend(fd, 0, data, 0);
	//send P1 ADC unit - 1
	XBeeUnitSend(fd, 1, "% 0");
	
	//send P2 ADC unit - 2
	XBeeUnitSend(fd, 2, "% 1");
	
	//send accel unit - X : 3/ Y : 4 / Z : 5
	XBeeUnitSend(fd, 3, "g_X");	
	XBeeUnitSend(fd, 4, "g_Y");
	XBeeUnitSend(fd, 5, "g_Z");
	
	//send lux unit - 6
	XBeeUnitSend(fd, 6, "lux");
	
	//send Temp unit - 7
	XBeeUnitSend(fd, 7, "C  ");
	
	
	// wait for the server to process
	sleep(1);
	
	
	while(fd)
	{
		//ADC
		pot[0] = 37.5; // 0 to 100 *10 (10bits)
		data[0] = (uint8_t)((uint32_t)(pot[0]*10)&0xFF);
		data[1] = (uint8_t)(((uint32_t)(pot[0]*10)>>8)&0xFF);
		XBeeDataSend(fd, 1, data, 2);
		
		pot[1] = 28.9; // 0 to 100 *10 (10bits)
		data[0] = (uint8_t)((uint32_t)(pot[1]*10)&0xFF);
		data[1] = (uint8_t)(((uint32_t)(pot[1]*10)>>8)&0xFF);
		XBeeDataSend(fd, 2, data, 2);
		
		// accel
		accel[0] = 0; // -2 to 2 -ish... *10 (5bits) each
		accel[1] = 0; // -2 to 2 -ish... *10 (5bits) each
		accel[2] = 120; // -2 to 2 -ish... *10 (5bits) each
		data[0] = (uint8_t)(accel[0]/12.8);
		XBeeDataSend(fd, 3, data, 1);
		data[0] = (uint8_t)(accel[1]/12.8);
		XBeeDataSend(fd, 4, data, 1);
		data[0] = (uint8_t)(accel[2]/12.8);
		XBeeDataSend(fd, 5, data, 1);
		
		// lux
		lux = 192; //0.045 to 188000 *10 (21bits)
		data[0] = (uint8_t)((uint32_t)(lux*10)&0xFF);
		data[1] = (uint8_t)(((uint32_t)(lux*10)>>8)&0xFF);
		data[2] = (uint8_t)(((uint32_t)(lux*10)>>16)&0xFF);
		XBeeDataSend(fd, 6, data, 3);
		
		//temp
		temp = 26.5; // -55 to 125 *10 
		data[0] = (uint8_t)((uint32_t)(temp*10)&0xFF);
		data[1] = (uint8_t)(((uint32_t)(temp*10)>>8)&0xFF);
		XBeeDataSend(fd, 7, data, 2);		
		
		
	}


	// closing serial port
	printf("closing serial ports\n");
	close(fd);

	return 0;
}

uint8_t XBeeDataSend(int fd, uint8_t id_capteur, uint8_t* data, int data_size)
// send a data
{
	int i;
	int size = data_size + 16;
	uint8_t msg[size];
	
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
	uint8_t write_buf[size + 4];
	
	// create buffer
	write_buf[0] = 0x7E; // start
	write_buf[1] = size>>8; // MSB size
	write_buf[2] = size; // LSB size
	
	// recopy msg into buffer
	for(i = 0; i < size; i++)
	{write_buf[3+i] = msg[i];}
	
	write_buf[3+size] = checksum(msg, size ); // checksum	
	
	int n = write(fd, &write_buf, sizeof write_buf);
	
	//wait for the server to process
	sleep(0.05);
	
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	
	return 0;
		
}


uint8_t XBeeUnitSend(int fd, uint8_t id_capteur, char* unit)
// send an unit
{
	int i;
	int unit_size = strlen(unit);
	int size = unit_size + 16;
	
	uint8_t msg[size];	

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
	{msg[16+i] = (uint8_t)unit[i];}	
		
	// create arrays
	uint8_t write_buf[size + 4];
	
	// create buffer
	write_buf[0] = 0x7E; // start
	write_buf[1] = size>>8; // MSB size
	write_buf[2] = size; // LSB size
	
	// recopy msg into buffer
	for(i = 0; i < size; i++)
	{write_buf[3+i] = msg[i];}
	
	write_buf[3+size] = checksum(msg, size ); // checksum	
	
	int n = write(fd, &write_buf, sizeof write_buf);
	
	//wait for the server to process
	sleep(0.05);
	
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	
	return 0;
		
}

