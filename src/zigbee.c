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


//Initialize serial port
int initport(int fd)
{
	int portstatus = 0;

	struct termios options;

	// Get the current options for the port...
	tcgetattr(fd, &options);

	// Set the baud rates to 9600...
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);

	// Enable the receiver and set local mode...
	options.c_cflag |= (CLOCAL | CREAD);

	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	//options.c_cflag |= SerialDataBitsInterp(8);     /* CS8 - Selects 8 data bits */
	options.c_cflag &= ~CRTSCTS;                      // Disable hardware flow control
	options.c_iflag &= ~(IXON | IXOFF | IXANY);       // Disable XON XOFF (for transmit and receive)
	//options.c_cflag |= CRTSCTS;                     /* Enable hardware flow control */

	options.c_cc[VMIN] = 1;   //Minimum characters to be read
	options.c_cc[VTIME] = 2;    //Time to wait for data (tenths of seconds)
	options.c_oflag &=~OPOST;
	options.c_iflag &=~(ICANON | ECHO | ECHOE | ISIG);
	// Set the new options for the port...
	tcsetattr(fd, TCSANOW, &options);

	//Set the new options for the port...
	tcflush(fd, TCIFLUSH);
	if (tcsetattr(fd, TCSANOW, &options) == -1)
	{
		perror("On tcsetattr:");
		portstatus = -1;
	}
	else
		portstatus = 1;

	return (portstatus);
}

int open_port(int USB_ID)
{

	int fd = open("/dev/ttyUSB"+USB_ID, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd == -1)
	{
		//Could not open the port
		perror("Open_port: Unable to open the port\n");
	}
	return (fd);
}



int checksum(unsigned short* frame)
// computes the checksum of the given frame
{
	int i;
	unsigned long sum = 0;
	
	for(i = 0; i < LENGTH(frame); i++)
	{sum += frame[i];}
	
	return 0xFF - (sum & 0xFF);
}

int sendAT(int serial_fd, char* reg)
// send an AT command
{

	int size = strlen(reg);
	unsigned short msg[size];
	
	int i;
	for(i = 0; i < size; i++)
	{msg[i] = (unsigned short)reg[i];}
	
	
	send(serial_fd, 8, msg);
	
	receive(serial_fd);
}




int send(int serial_fd, int code, unsigned short* msg)
// send an command to the serial port
{
	int i;
	printf("%lu\n", LENGTH(msg));
	// create arrays
	unsigned short frame[LENGTH(msg)/2 + 6];
	unsigned short sub[LENGTH(msg)/2 + 2];
		
	sub[0] = code; // code request
	sub[1] = 0x01; // id
	
	// creating frame data for size and checksum
	for(i = 0; i < LENGTH(msg); i++)
	{sub[2+i] = msg[i];}
	
	frame[0] = 0x7E; // start
	frame[1] = LENGTH(sub)>>8; // MSB size
	frame[2] = LENGTH(sub) & 0xFF; // LSB size
	
	// recopy sub into frame
	for(i = 0; i < LENGTH(sub); i++)
	{frame[3+i] = sub[i];}
	
	frame[3+LENGTH(sub)] = checksum(sub); // checksum
	
	char write_buf[2*LENGTH(frame)];
	
	// fill buffer to send
	for(i = 0; i < LENGTH(frame); i++)
	{sprintf(&write_buf[i] + i*sizeof(char),"%02X",frame[i]);}
	
	printf("\nbuffer content: \n");	
	for(i = 0; i < sizeof(write_buf); i++)
	{printf("%c",write_buf[i]);}
	
	/*
	int n = write(serial_fd, &write_buf, sizeof write_buf);
	
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	else
	{
		printf("Successfully wrote %lu bytes\n", sizeof write_buf);
		
		for (i=0; i<n; i++)
		{
			printf("%c ",write_buf[i]);
		}
	}*/
}



int receive(int serial_fd)
{
	// get size data from serial port
	unsigned short read_header[3];
	int n = read(serial_fd, read_header, sizeof read_header);
	int size = read_header[2] + (read_header[1]<<8);


	// get data from serial port
	char read_data[size + 1];
	n = read(serial_fd, read_data, sizeof read_data);
	
	if (n < 0)
         fputs("Reading failed!\n", stderr);
     else
     {
         printf("Successfully read from serial port -- %s\n With %d Bytes", read_data,n);
     }
		
}

/*----------------------------------------------------------------------------------------------*/
