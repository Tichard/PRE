/*----------------------------------ZIGBEE.C----------------------------------*/
/*
 *> [File Name] zigbee.c
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] alpha
 *> [Author] Richard
 *> [Language] C
 *> [Description] ZIGBEE API : 
 *> allows communication with the ZIGBEE
 */

#include "zigbee.h"


int serial_open(char* serial_name, int baudrate)
//Open and init serial port
{
    	struct termios tty;
	memset (&tty, 0, sizeof tty);	
	
	int fd = open( serial_name, O_RDWR| O_NOCTTY | O_NDELAY);
	fcntl(fd, F_SETFL, 0);
	
	/* Error Handling */
	if ( tcgetattr ( fd, &tty ) != 0 )
	{//fputs( "Error %d from tcgetattr: %s\n",errno, strerror(errno) );}
	
	/* Set Baud Rate */
	cfsetospeed (&tty, baudrate);
	cfsetispeed (&tty, baudrate);
	
	/* Setting flags */
	tty.c_cflag     |=  (CREAD | CLOCAL);     // turn on READ & ignore ctrl lines
	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG);
	tty.c_oflag     &=  ~OPOST;
	tty.c_cc[VMIN]   =  1;		// get at least 1 data
	tty.c_cc[VTIME]  =  1;		// 0.1 seconds read timeout
	
	
	/* Make 8-N-1 */
	tty.c_cflag     &=  ~PARENB;
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;
	
	tty.c_cflag     &=  ~CRTSCTS;
	tty.c_cflag     &=  ~(IXOFF | IXON);	
	
	/* Make raw */
	cfmakeraw(&tty);
	
	/* Flush Port, then applies attributes */
	tcflush( fd, TCIFLUSH );
	if ( tcsetattr ( fd, TCSANOW, &tty ) != 0)
	{//fputs( "Error %d from tcsetattr: %s\n",errno, strerror(errno) );}
		
	return fd;
}


int str2hex(char* str, uint8_t* hex)
// convert string to a Hexa array
{
	int size = strlen(str);
	
	int i;
	for(i = 0; i < size; i++)
	{
		hex[i] = (int8_t)str[i];
	}	
}


int checksum(uint8_t* frame, unsigned long size)
// computes the checksum of the given frame
{
	int i;
	int8_t sum = 0;
	
	for(i = 0; i < size; i++)
	{
		sum += frame[i];
	}
	
	return 0xFF - (sum & 0xFF);
}


int sendFrameType(int serial_fd, uint8_t type, uint8_t* data, int data_size ,uint8_t frame_id, uint64_t dest64, uint16_t dest16)
// switch case regarding the frame type
{
	int8_t msg[ data_size + 13 ]; // max size possible
	int size;
	int i;	
	
	switch (type&0xFF){
		case 0x08 : // AT command
		{
			// ID
			msg[0] = frame_id;
			// Data
			for( i = 0; i<data_size; i++)
			{msg[1+i] = data[i];}
			
			
			size = data_size + 1;
					
			break;
		}
		case 0x10 : // Transmit request
		{	
			// ID
			msg[0] = frame_id;
			// 64-bits Destination address
			msg[1] = (dest64>>56);
			msg[2] = (dest64>>48);
			msg[3] = (dest64>>40);
			msg[4] = (dest64>>32);
			msg[5] = (dest64>>24);
			msg[6] = (dest64>>16);
			msg[7] = (dest64>> 8);
			msg[8] = (dest64);
			// 16-bits Destination Network address
			msg[9]  = (dest16>>8);
			msg[10] = (dest16);
			// Broadcast radius
			msg[11] = 0x00 ;
			// options
			msg[12] = 0x00 ;
			
			// data
			for( i = 0; i<data_size; i++)
			{msg[13+i] = data[i];}
			
			
			size = data_size + 13;
					
			break;
		}
		case 0x11 : // Explicit addressing ZigBee command frame
		{
			break;
		}
		case 0x17 : // Remote AT command request
		{
			// ID
			msg[0] = frame_id;
			// 64-bits Destination address
			msg[1] = (dest64>>56);
			msg[2] = (dest64>>48);
			msg[3] = (dest64>>40);
			msg[4] = (dest64>>32);
			msg[5] = (dest64>>24);
			msg[6] = (dest64>>16);
			msg[7] = (dest64>> 8);
			msg[8] = (dest64);
			// 16-bits Destination Network address
			msg[9]  = (dest16>>8);
			msg[10] = (dest16);
			// Remote command options
			msg[11] = 0x02 ;
			
			// data
			for( i = 0; i<data_size; i++)
			{msg[12+i] = data[i];}
			
			
			size = data_size + 12;
			
			
			break;
		
		}
		case 0x21 : // Create source route
		{
			break;
		}
		case 0x8A : // Modem status
		{
			break; 
		}

		default :
			fputs("unknown code!\n", stderr);
			return -1;			
	}

	// send the message	
	send(serial_fd,type,msg,size);	
	
	return 0;
}


int send(int serial_fd, int type, uint8_t* msg, unsigned long size)
// send an message to the serial port
{
	int i;
		
	// create arrays
	int8_t write_buf[size + 5];
	int8_t sub[size + 1];
		
	sub[0] = type; // frame type
	
	// creating frame data for size and checksum
	for(i = 0; i < size; i++)
	{sub[1+i] = msg[i];}
	
	write_buf[0] = 0x7E; // start
	write_buf[1] = LENGTH(sub)>>8; // MSB size
	write_buf[2] = LENGTH(sub); // LSB size
	
	// recopy sub into frame
	for(i = 0; i < LENGTH(sub); i++)
	{write_buf[3+i] = sub[i];}
	
	write_buf[3+LENGTH(sub)] = checksum(sub, LENGTH(sub) ); // checksum
	
	
	int n = write(serial_fd, &write_buf, sizeof write_buf);
	
	if (n < 0)
		fputs("sending message failed!\n", stderr);
		
	char flush[1];
	receive(serial_fd,flush);
}
		

int receive(int serial_fd, char* data)
{
	// declare variables
	int totSize;
	int size;
	int index;
	int i;
	int n;
	
	int return_data;

	// read header
	totSize = 3;	
	size = totSize;
	index = 0;	
	
	// allocate the header array
	uint8_t read_header[totSize];
	
	// get size data from serial port
	while(size > 0)
	{			
		// get data from serial port
		n = read(serial_fd, &read_header[index], size);
		
		// case of error : no data read on port
		if (n < 0 )
		{
       			fputs("Reading header failed!\n", stderr);
       		}     		
       	
		size -= n;
		index += n;
	}	
	
	// read data
	totSize = (uint8_t)read_header[2] | (uint8_t)(read_header[1]<<8);
	totSize += 1; // checksum byte
	
	size = totSize;
	index = 0;
	
	// allocate the data array
	uint8_t read_data[totSize];
	
	//assert if 1st bytes is start byte (0x7E)
	if (read_header[0] == 0x7E)
	{
		n = 0;		
		while(size > 0)
		{		
			// get data from serial port
			n = read(serial_fd, &read_data[index], size);
			
			// case of error : no data read on port
			if (n < 0 )
			{
        			fputs("Reading data failed!\n", stderr);
        		}     		
        	
			size -= n;
			index += n;
		}
		
		switch (read_data[0])
		{
			case 0x88 : // AT command response
			{
				printf("receive AT response from %u status : %u\n",read_data[1],read_data[4]);
				
				break;
			}
			case 0x8A : // Zigbee transmit status
			{
				printf("receive modem status from %d status : %d\n",read_data[1],read_data[2]);
				
				break;
			}
			case 0x8B : // Zigbee transmit status
			{
				printf("receive transmit status from %d status : %d\n",read_data[1],read_data[5]);
				
				break;
			}
			case 0x90 : // ZigBee receive packet
			{
				return_data = 0;				
				//char* unit;
				char unit[3];
				uint16_t addr16 = ((uint16_t)read_data[9]<<8) | read_data[10];
				
				for (i=0; i<totSize-14; i++)
				{
					return_data = return_data<<(8*i) | read_data[13 + i];
				}
				
				// get unit from 16-bits address
				for ( i = 1; i<=ID_Board;i++)
				{				
					if(addr[i].addr16 == addr16)
					{					
						
						if (*(addr[i].unit[read_data[12]]) == 0) rame
						{
							// if unit isn't define, it's the first trame received -> unit 
							sprintf( addr[i].unit[read_data[12]], "%c%c%c",read_data[13], read_data[14], read_data[15]);
														
							// return NULL
							*(data)=0;
							
							return 0;						
						}
						
						break;
					}
				}
				sprintf(data,"%d%s",return_data,addr[i].unit[read_data[12]]);
				
				break;				
				
			}
			case 0x91 : // ZigBee receive packet (more detailed)
			{
								
				break;
			}
			case 0x92 : // ZigBee IO Data sample
			{
				break;
			}
			case 0x94 : // ZigBee sensor read Indicator
			{
				break;
			}
			case 0x95 : // Node Identification Indicator
			{	
				uint64_t addr64 = 	(((uint64_t)read_data[1])<<56) |
									(((uint64_t)read_data[2])<<48) |
									(((uint64_t)read_data[3])<<40) | 
									(((uint64_t)read_data[4])<<32) | 
									(((uint64_t)read_data[5])<<24) | 
									(((uint64_t)read_data[6])<<16) | 
									(((uint64_t)read_data[7])<< 8) | 
									((uint64_t)read_data[8]);
									
				uint16_t addr16 = ((uint16_t)read_data[9]<<8) | read_data[10];
				
				
				// check if 64-bits address already exists
				for ( i = 1; i<=ID_Board;i++)
				{				
					if(addr[i].addr64 == addr64) // if so, update 16-bits address
					{
						
						printf("\nupdating address...");
						addr[i].addr16 = addr16;
						
						int j;
						for ( j = 0; j<=255;j++)
						{*(addr[i].unit[j]) = 0;}
						break;
					}
				}
				
				// if wasn't found in the table, add a new element
				if (i > ID_Board)
				{
					printf("\ncreating address...");
					ID_Board++;
					addr[ID_Board].addr64 = addr64;
					addr[ID_Board].addr16 = addr16;				
				}
				
				// return NULL
				*(data)=0;
				
				break;
			}
			case 0x97 : // remote command response
			{
				break;
			}
			default :			
				// return NULL
				*(data)=0;
				
				fputs("unknown code!\n", stderr);
				return -1;			
		}
		
	}
	
	return 0;
}

/*----------------------------------------------------------------------------------------------*/
