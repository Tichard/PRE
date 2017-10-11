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
int serial_open(char *serial_name, int baud)
{
      /* Open File Descriptor */
	int USB = open( "/dev/ttyUSB0", O_RDWR| O_NONBLOCK | O_NDELAY );

	
	/* *** Configure Port *** */
	struct termios tty;
	memset (&tty, 0, sizeof tty);

	/* Set Baud Rate */
	cfsetospeed (&tty, B9600);
	cfsetispeed (&tty, B9600);
	
	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;        // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;
	tty.c_cflag     &=  ~CRTSCTS;       // no flow control
	tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical 	processing
	tty.c_oflag     =   0;                  // no remapping, no delays
	tty.c_cc[VMIN]      =   0;                  // read doesn't block
	tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout
	
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
	tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
	tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
	tty.c_oflag     &=  ~OPOST;              // make raw
	
	/* Flush Port, then applies attributes */
	tcflush( USB, TCIFLUSH );

	
	return USB;
}


int checksum(unsigned short* frame, unsigned long size)
// computes the checksum of the given frame
{
	int i;
	unsigned long sum = 0;
	
	for(i = 0; i < size; i++)
	{
		sum += frame[i];
	}
	
	return 0xFF - (sum & 0xFF);
}

int sendAT(int serial_fd, char* reg)
// send an AT command
{

	int size = strlen(reg);
	unsigned short msg[size];
	
	int i;
	for(i = 0; i < size; i++)
	{
		msg[i] = (unsigned short)reg[i];
	}
	
	
	send(serial_fd, 8, msg, size);
	
	//receive(serial_fd);
}




int send(int serial_fd, int code, unsigned short* msg, unsigned long size)
// send an command to the serial port
{
	int i;
	
	
	// create arrays
	unsigned short frame[size + 6];
	unsigned short sub[size + 2];
		
	sub[0] = code; // code request
	sub[1] = 0x01; // id
	
	// creating frame data for size and checksum
	for(i = 0; i < size; i++)
	{sub[2+i] = msg[i];}
	
	frame[0] = 0x7E; // start
	frame[1] = LENGTH(sub)>>8; // MSB size
	frame[2] = LENGTH(sub) & 0xFF; // LSB size
	
	// recopy sub into frame
	for(i = 0; i < LENGTH(sub); i++)
	{frame[3+i] = sub[i];}
	
	frame[3+LENGTH(sub)] = checksum(sub, LENGTH(sub) ); // checksum
	
	char write_buf[ 2* LENGTH(frame)];
	
	// fill buffer to send
	for(i = 0; i < LENGTH(frame); i++)
	{
		sprintf(&write_buf[0] + i* 2*sizeof(char),"%02X",frame[i]);
	}
	
	
	printf("\nbuffer content: \n");	
	for(i = 0; i < 2* LENGTH(frame); i++)
	{printf("%c",write_buf[i]);}
	
	printf("\nsending... \n");	--
	
	int n = write(serial_fd, &write_buf, sizeof write_buf);
	
	if (n < 0)
		fputs("sending message failed!\n", stderr);
	else
	{
		printf("Successfully wrote %lu bytes\n", sizeof write_buf);
		
		for (i=0; i<n; i+=2)
		{
			printf("%c%c ",write_buf[i], write_buf[i+1]);
		}
		printf("\n");
	}
}



int receive(int serial_fd)
{
	// get size data from serial port
	unsigned short read_header[3];
	int n = read(serial_fd, read_header, sizeof read_header);
	int size = read_header[2] + (read_header[1]<<8);

	printf("\nsize :%d \n",size);

	// get data from serial port
	char read_data[size + 1];
	n = read(serial_fd, read_data, sizeof read_data);
	
	if (n < 0)
         fputs("Reading failed!\n", stderr);
     else
     {
         printf("Successfully read from serial port -- %s\n With %d Bytes\n", read_data,n);
     }
		
}

/*----------------------------------------------------------------------------------------------*/
