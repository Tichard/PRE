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
		else if (!strcmp(argv[1],"R1"))
		{
			printf("starting test in Routeur Mode\n");
			mainRout1();
		}
		else if (!strcmp(argv[1],"R2"))
		{
			printf("starting test in Routeur Mode\n");
			mainRout2();
		}
		else 
		{
			printf("wrong argument\n");
		}
	}

}


int mainCoord(void)
{	
	ID_Board = 0; // number of currently connected board
	
	int coord = serial_open("/dev/ttyUSB0",9600);
	
	
	printf("\n------------ START OF TEST --------------\n");
	char data[16];
	while(1)
	{
		receive(coord, data);
		if(data!=NULL){printf("%s\n",data);}
	}

	printf("\n------------- END OF TEST --------------\n\n");
	// closing serial port
	printf("closing serial ports\n");
	close(coord);

	return 0;
}


int mainRout1(void)
{	

	int rout = -1;
	
	// wait for the zigbee to be connected
	while (rout<0){rout = serial_open("/dev/ttyUSB1",9600);}
	
	
	printf("\n------------ START OF TEST --------------\n");
	
	// receive 0x8A
	char flush[1];
	receive(rout,flush);	
	
	// send unit
	char* unit = "lux";
    int size = strlen(unit);    
    
    // convert data string to hexa
	uint8_t unit_hex[size];		
	str2hex(unit,unit_hex);
	uint8_t unit_code[4] = {0x01, unit_hex[0], unit_hex[1], unit_hex[2]};
	
	sendFrameType(rout, 0x10, unit_code, 4, 0x01, 0x0000000000000000, 0x0000);
	

	printf("\n-------------- SEND DATA ---------------\n\n");
	
	uint8_t data[3] = {0x01,0x1E,0x0F};//7695
	
	int i = 0;
	while(i<10)
	{
		
		sendFrameType(rout, 0x10, data, LENGTH(data), 0x01, 0x0000000000000000, 0x0000); //0x0013A2004089EBE
		
		sleep(0.1);
		i++;
	}


	printf("\n------------- END OF TEST --------------\n\n");
	// closing serial port
	printf("closing serial ports\n");
	close(rout);

	return 0;
}

int mainRout2(void)
{	

	int rout = -1;
	
	// wait for the zigbee to be connected
	while (rout<0){rout = serial_open("/dev/ttyUSB2",9600);}
	
	
	printf("\n------------ START OF TEST --------------\n");
	
	// receive 0x8A
	char flush[1];
	receive(rout,flush);
	
	// send unit
	char* unit = "dB ";
    int size = strlen(unit);    
    
    // convert data string to hexa
	uint8_t unit_hex[size];		
	str2hex(unit,unit_hex);
	uint8_t unit_code[4] = {0x01, unit_hex[0], unit_hex[1], unit_hex[2]};
	
	sendFrameType(rout, 0x10, unit_code, 4, 0x01, 0x0000000000000000, 0x0000);
	

	printf("\n-------------- SEND DATA ---------------\n\n");
	
	uint8_t data[2] = {0x01,0xAA};// 170
	
	
	int i = 0;
	while(i<10)
	{
		
		sendFrameType(rout, 0x10, data, LENGTH(data), 0x01, 0x0000000000000000, 0x0000); //0x0013A2004089EBE
		
		sleep(0.1);
		i++;
	}


	printf("\n------------- END OF TEST --------------\n\n");
	// closing serial port
	printf("closing serial ports\n");
	close(rout);

	return 0;
}


