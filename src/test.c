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
#include "table.h"


int main(void)
{
	
    char* text = "MY";
    int size = strlen(text);
    
    // convert data string to hexa
	uint8_t data_hex[size];		
	str2hex(text,data_hex);
	
	
	printf("\n-----------------AT COMMAND-------------------\n\n");
	
	int coord = serial_open("/dev/ttyUSB0",9600);
	
	sendFrameType(coord, 0x08, data_hex, size, 0x01, 0, 0);
	printf("\n\n");
	receive(coord);
	printf("\n\n");
	
	printf("\n-----------------NEW MODULE-------------------\n\n");
	
	receive(coord);
	printf("\n\n");
	int rout1 = serial_open("/dev/ttyUSB1",9600);
	
	printf("\n--------------SEND DATA- C -> R ---------------\n\n");
	
	uint8_t board = 0;
	printf("ID_Board : %d\n", ID_Board);
	
	printf("addr64 : %016lX\n",addr[board].addr64);
	printf("addr16 : %04X\n",addr[board].addr16);
	
	sendFrameType(coord, 0x10, data_hex, size, board, addr[board].addr64, addr[board].addr16);
	printf("\n\n");
	receive(coord);
	printf("\n\n");
	
	receive(rout1);
	printf("\n\n");
	
	printf("\n--------------SEND DATA- R -> C ---------------\n\n");
	
	
	
	sendFrameType(rout1, 0x10, data_hex, size, 0x01, 0x0000000000000000, 0x0000); //0x0013A2004089EBE2
	printf("\n\n");
	receive(rout1);
	printf("\n\n");
	
	receive(coord);
	printf("\n\n");


	// closing serial port
	printf("closing serial ports\n");
	close(coord);
	close(rout1);

	return 0;
}

