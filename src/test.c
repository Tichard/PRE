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
	
    //sendAT(serial_fd,"MY");
    
    char* text = "TxData0A";
    
    // convert data string to hexa
	int8_t data_hex[strlen(text)];		
	str2hex(text,data_hex);
    
	sendFrameType(serial_fd, 0x10, data_hex, 0x01, 0x0013A200400A0127, 0xFFFE);
	
	receive(serial_fd);

	close(serial_fd);

	return 0;
}

