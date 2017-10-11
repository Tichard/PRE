/*----------------------------------TEST.C----------------------------------*/
/*
 *> [File Name] test.c
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] alpha
 *> [Author] Richard
 *> [Language] C
 *> [Description] ZIGBEE API : 
 *> allows communication with the ZIGBEE
 */

#include "zigbee.h"


int main(void)
{
	//int serial_fd = open_port(1);
	
    sendAT(1,"JNDDDDDDDD");
    unsigned short msg[2] = {0x4A, 0x4E};
    
    send(1, 0x08, msg );
	//close(serial_fd);

	return 0;
}

