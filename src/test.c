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
	ID_Board = 0;
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
	
	printf("\n----------------NEW MODULE 1------------------\n\n");
	
	receive(coord);
	printf("\n\n");
	int rout1 = serial_open("/dev/ttyUSB1",9600);
	
	/*
	printf("\n----------------NEW MODULE 2------------------\n\n");
	
	receive(coord);
	printf("\n\n");
	int rout2 = serial_open("/dev/ttyUSB2",9600);
	
	
	printf("\n--------------REPLUG MODULE 1-----------------\n\n");
	
	receive(coord);
	printf("\n\n");
	
	
	
	printf("\n-----------------VIEW TABLE--------------------\n\n");
	
	int i;			
	for ( i = 0; i<=ID_Board;i++)
	{
		printf("table[%d] -> addr64 : %016lX   -> addr16 : %04X   \n",i,addr[i].addr64,addr[i].addr16);
	}
	*/
	
	
	printf("\n--------------SEND DATA- C -> R ---------------\n\n");
	uint8_t board = 0x01;
	
	sendFrameType(coord, 0x10, data_hex, size, board, addr[board].addr64, addr[board].addr16);
	
	printf("\n\nreceive coord:\n");
	receive(coord);
	
	printf("\n\nreceive rout1:\n");	
	receive(rout1);
	
	printf("\n\n");
	
	printf("\n--------------SEND DATA- R -> C ---------------\n\n");
	
	
	
	sendFrameType(rout1, 0x10, data_hex, size, 0x01, 0x0000000000000000, 0x0000); //0x0013A2004089EBE2
	printf("\n\nreceive rout1:\n");	
	receive(rout1);
	
	printf("\n\nreceive coord:\n");
	receive(coord);
	
	printf("\n\n");


	// closing serial port
	printf("closing serial ports\n");
	close(coord);
	close(rout1);

	return 0;
}

