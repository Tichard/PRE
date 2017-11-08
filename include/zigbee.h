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
#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__


// Standart C librairies
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

// Project Header files
#include "table.h"


#define LENGTH(x) (sizeof(x) / sizeof((x)[0]))

int mainCoord(void);
int mainRout1(void);
int mainRout2(void);

int str2hex(char*, uint8_t*);
int serial_open(char *, int);
int checksum(uint8_t*, unsigned long);
int sendFrameType(int, uint8_t, uint8_t*, int, uint8_t, uint64_t, uint16_t);
int send(int, int, uint8_t*, unsigned long);
int receive(int,char*);

#endif




