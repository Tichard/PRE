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


//Open and init serial port
int serial_open(char *serial_name, int baudrate)
{


    struct termios tty;
	memset (&tty, 0, sizeof tty);
	
	
	int fd = open( "/dev/ttyUSB0", O_RDWR| O_NOCTTY | O_NDELAY);
	fcntl(fd, F_SETFL, 0);
	
	/* Error Handling */
	if ( tcgetattr ( fd, &tty ) != 0 )
	{
		printf( "Error %d from tcgetattr: %s\n",errno, strerror(errno) );
	}
	
	/* Set Baud Rate */
	cfsetospeed (&tty, baudrate);
	cfsetispeed (&tty, baudrate);
	
	/* Setting flags */
	tty.c_cflag     |=  (CREAD | CLOCAL);     // turn on READ & ignore ctrl lines
	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG);
	tty.c_oflag     &=  ~OPOST;
	tty.c_cc[VMIN]   =  3;                  // get at least header size (start + size)
	tty.c_cc[VTIME]  =  5;                  //0.5 seconds read timeout
	
	
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
	{
	   printf( "Error %d from tcsetattr: %s\n",errno, strerror(errno) ); 	   
	}
	
	return fd;
	
}

int str2hex(char* str, int8_t* hex)
// convert string to a Hexa array
{

	int size = strlen(str);
	
	int i;
	for(i = 0; i < size; i++)
	{
		hex[i] = (int8_t)str[i];
	}
	
}
int checksum(int8_t* frame, unsigned long size)
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

int sendFrameType(int serial_fd, int8_t type, int8_t* data, int8_t frame_id, int64_t dest64, int16_t dest16)
// switch case regarding the frame type
{
	
	int8_t msg[ LENGTH(data) + 13 ]; // max size possible
	int size;
	int i;
	
	switch (type){
		case 0x08 : // AT command
		
			// ID
			msg[0] = frame_id;
			// Data
			for( i = 0; i<LENGTH(data); i++)
			{msg[1+i] = data[i];}
			
			
			size = LENGTH(data) + 1;
			
		
		break;
		
		case 0x10 : // Transmit request
				
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
			for( i = 0; i<LENGTH(data); i++)
			{msg[13+i] = data[i];}
			
			
			size = LENGTH(data) + 13;
					
		break;
			
//		case 0x11 : // Explicit addressing ZigBee command frame
		
		case 0x17 : // Remote AT command request
		
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
			for( i = 0; i<LENGTH(data); i++)
			{msg[12+i] = data[i];}
			
			
			size = LENGTH(data) + 12;
			
			
		break;
		
			
//		case 0x21 : // Create source route
			
//		case 0x8A : // Modem status 

		default :
			fputs("unknown code!\n", stderr);
			return -1;
			
		}

		
		// send the message	
		send(serial_fd,type,msg,size);	

	
	return 0;
}


int send(int serial_fd, int type, int8_t* msg, unsigned long size)
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
	write_buf[2] = LENGTH(sub) & 0xFF; // LSB size
	
	// recopy sub into frame
	for(i = 0; i < LENGTH(sub); i++)
	{write_buf[3+i] = sub[i];}
	
	write_buf[3+LENGTH(sub)] = checksum(sub, LENGTH(sub) ); // checksum
	
	
	printf("sending... \n");
	
	int n = write(serial_fd, &write_buf, sizeof write_buf);
	
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	else
	{
		printf("Successfully wrote %lu bytes\n", sizeof write_buf);
		
		for (i=0; i<n; i++)
		{
			printf("%02X ",write_buf[i]&0xFF);
		}
		printf("\n");
	}
}

int receive(int serial_fd)
{

	// get size data from serial port
	int8_t read_header[3];
	
	
	printf("reading header... \n");
	int n = read(serial_fd, &read_header, sizeof read_header);
	int size = (int8_t)read_header[2] + (int8_t)(read_header[1]<<8);

	// get data from serial port
	int8_t read_data[size + 1];
	
	//assert if 1st bytes is start byte (0x7E)
	if (read_header[0] == 0x7E)
	{
		printf("reading data... \n");
		n = read(serial_fd, &read_data, sizeof read_data);
	
		if (n < 0 )
        	fputs("Reading failed!\n", stderr);
        else if (n!=size+1)
        	fputs("Not enough bytes read!\n", stderr);
    	else
     	{
        	printf("Successfully read from serial port %d bytes, %d bytes expected\n",n, size+1);
        
        	int i;
        	for (i=0; i<n; i++)
			{
				printf("%02X ",read_data[i]&0xFF);
			}
			printf("\n");
		
    	}
     
	}
	
		
}

/*----------------------------------------------------------------------------------------------*/
