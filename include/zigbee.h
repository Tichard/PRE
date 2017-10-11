/*----------------------------------ZIGBEE.H----------------------------------*/
/*
 *> [File Name] zigbee.h
 *> [Platform] PRE ENIB
 *> [Version] alpha
 *> [Author] Richard
 *> [Language] C
 *> [Description] ZIGBEE API : 
 *> allows communication with the ZIGBEE
 */
#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>


#define LENGTH(x) (sizeof(x) / sizeof((x)[0]))

int serial_open(char *, int);
int checksum(unsigned short*, unsigned long);
int sendAT(int, char*);
int send(int, int, unsigned short*, unsigned long);
int receive(int);
int main(void);


#endif




