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

int str2hex(char*, int8_t*);
int serial_open(char *, int);
int checksum(int8_t*, unsigned long);
int sendFrameType(int, int8_t, int8_t*, int8_t, int64_t, int16_t);
int sendAT(int, char*);
int send(int, int, int8_t*, unsigned long);
int receive(int);

#endif




