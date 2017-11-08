/*----------------------------------TABLE.H----------------------------------*/
/*
 *> [File Name] table.h
 *> [Platform] PRE ENIB
 *> [Version] alpha
 *> [Author] Richard
 *> [Language] C
 *> [Description] ADDRESSES AND UNITS TABLES : 
 *> declare the table for the adresses and the units
 */
#ifndef __TABLE_H__
#define __TABLE_H__

struct Addresses {
   uint64_t addr64;
   uint16_t addr16;
};

int ID_Board;
struct Addresses addr[256];
char unit[256][256][3];

#endif
