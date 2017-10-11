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
	tty.c_cc[VMIN]   =  3;                  // read doesn't block
	tty.c_cc[VTIME]  =  0;                  // blocking waiting//0.5 seconds read timeout
	
	
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

int sendAT(int serial_fd, char* reg)
// send an AT command
{

	int size = strlen(reg);
	int8_t msg[size];	
	
	str2hex(reg, msg);
	
	send(serial_fd, 0x08, msg, size);
	
	receive(serial_fd);
}

int send(int serial_fd, int code, int8_t* msg, unsigned long size)
// send an command to the serial port
{
	int i;
		
	// create arrays
	int8_t frame[size + 6];
	int8_t sub[size + 2];
		
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
	
	int8_t write_buf[2*LENGTH(frame)];
	
	// fill buffer to send
	for(i = 0; i < LENGTH(frame); i++)
	{
		sprintf(&write_buf[0] + i * 2*sizeof(int8_t),"%02X",frame[i]);
	}
	
	printf("\nsending... \n");
	
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
	int8_t read_header[3];
	
	
	printf("\nreading header... \n");
	int n = read(serial_fd, &read_header, sizeof read_header);
	int size = (int8_t)read_header[2] + (int8_t)(read_header[1]<<8);

	printf("\nstart :%c \n",read_header[0]);
	printf("\nsize :%d \n",size);

	// get data from serial port
	int8_t read_data[size + 1];
	
	printf("\nreading data... \n");
	n = read(serial_fd, &read_data, sizeof read_data);
	
	if (n < 0)
         fputs("Reading failed!\n", stderr);
     else
     {
         printf("Successfully read from serial port  %d Bytes\n",n);
     }
		
}

/*----------------------------------------------------------------------------------------------*/
