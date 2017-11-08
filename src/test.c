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

int main ( int argc, char *argv[] )
{
	if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf("failed starting test\n");
    }
    else 
    {
		if (!strcmp(argv[1],"C"))
		{
			printf("starting test in Coordinator Mode\n");
			mainCoord();
		}
		else if (!strcmp(argv[1],"R"))
		{
			printf("starting test in Routeur Mode\n");
			mainRout();
		}
		else 
		{
			printf("wrong argument\n");
		}
	}

}


int mainCoord(void)
{	
	ID_Board = 1;
	int coord = serial_open("/dev/ttyUSB0",9600);
	
	printf("\n-------------- INIT BOARD ---------------\n\n");
	
	printf("connexion carte\n");
	receive(coord);	
	printf("\n\n");
	
	printf("\n-------------- SEND DATA ---------------\n\n");
	
	int i = 0;
	while(i<10)
	{
		printf("\n\n");
		receive(coord);
		
		printf("\n\n");
		i++;
	}

	printf("\n------------- END OF TEST --------------\n\n");
	// closing serial port
	printf("closing serial ports\n");
	close(coord);

	return 0;
}

int mainRout(void)
{	

	// FPGA w/ 3 sensor
	//  - 1 luminosity  (lux)
	//  - 2 pressure  (hPa)
	//  - 3 sound  (dB )
	
	uint8_t ID_FPGA;
	
	int rout = -1;
	
	// wait for the zigbee to be connected
	while (rout<0){rout = serial_open("/dev/ttyUSB1",9600);}
	
	printf("\n-------------- INIT BOARD ---------------\n\n");
	printf("\n\n");	
	
	
	
	// receive 0x8A
	printf("connexion carte\n");
	receive(rout);	
	printf("\n\n");
	
	
	
	// receiveID	
	printf("transfert d'ID\n");
	ID_FPGA = receiveID(rout);	
	printf("\n\n");




	// send unit 1
	printf("transfert d'unité\n");
	char* text = "lux";
    int size = strlen(text);    
    
    // convert data string to hexa
	uint8_t data_hex[size];		
	str2hex(text,data_hex);
	
	sendFrameType(rout, 0x10, data_hex, size, 0x01, 0x0000000000000000, 0x0000);		
	printf("\n\n");
	

	printf("\n-------------- SEND DATA ---------------\n\n");
	
	uint8_t data[2];
	data[0] = 0x04; 
	data[1] = 0x1A;
	
	int i = 0;
	while(i<10)
	{
		int val = sendFrameType(rout, 0x10, data, LENGTH(data), 0x01, 0x0000000000000000, 0x0000); //0x0013A2004089EBE
		sleep(1);
		i++;
	}



	printf("\n------------- END OF TEST --------------\n\n");
	// closing serial port
	printf("closing serial ports\n");
	close(rout);

	return 0;
}


