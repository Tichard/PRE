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
	ID_Board = 0; // number of currently discovered board
	
	int coord = serial_open("/dev/ttyUSB0",9600);
	
	char data[16];
	while(1)
	{
		if(receive(coord, data)){printf("%s\n",data);}
		sleep(0.5);
	}


	// closing serial port
	printf("closing serial ports\n");
	close(coord);

	return 0;
}
