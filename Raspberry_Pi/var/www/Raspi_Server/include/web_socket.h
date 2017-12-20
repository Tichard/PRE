/*----------------------------------WEBSOCKET.H----------------------------------*/
/*
 *> [File Name] websocket.h
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] V1.4
 *> [Author] Richard
 *> [Language] C
 *> [Description] websocket API : 
 *> websocket API header 
 */

// Standard C librairies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// Project Header files
#include <libwebsockets.h>
#include "jWrite.h"
#include "table.h"

// structures and define

static unsigned int BUFF_SIZE = 16384;
static char* buffer;
unsigned int id_carte,id_capteur;

static int destroy_flag = 0;

static void INT_HANDLER(int signo) {
    destroy_flag = 1;
}


// Functions prototypes
int ws_start(int);
int websocket_write_str(struct lws *, char *, int);

int writeFile(char*);
static int ws_service_callback(struct lws *, enum lws_callback_reasons , void*, void *, size_t);
