/*----------------------------------TEST.C----------------------------------*/
/*
 *> [File Name] test.c
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] alpha
 *> [Author] Richard
 *> [Language] C
 *> [Description] ZIGBEE API : 
 *> api test module
 */

#include "zigbee.h"


int main(void)
{
	int serial_fd = serial_open("/dev/ttyUSB0",9600);
	
    	sendAT(serial_fd,"NJ");
    

	close(serial_fd);

	return 0;
}

