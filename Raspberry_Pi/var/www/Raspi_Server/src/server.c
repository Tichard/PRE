/*----------------------------------SERVER.C----------------------------------*/
/*
 *> [File Name] server.c
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] V1.4
 *> [Author] Richard & Norbert
 *> [Language] C
 *> [Description] SERVER : 
 *> get XBee data and write into json file 
 */

// Standard C librairies
#include <sys/stat.h>
#include <time.h>

// Project Header files
#include "zigbee.h"
#include "web_socket.h"


static void *pthread_XBee()
{

	int millisec_sleep = 20; 
	struct timespec ts;
	ts.tv_sec = millisec_sleep/1000;
	ts.tv_nsec = (millisec_sleep%1000)*1000000;

	ID_Board = 0; // number of currently discovered board
	int coord = serial_open("/dev/ttyUSB0",9600);
	char data[32];
	
	int carte,capteur,val;		
	unsigned int i;
	
	char *p = NULL;
	
    for(;;)
    {		
		// Receiving of the data
		if(receive(coord, data))
		{		
			p = strtok(data, ",");
			i=0;		   
			// Parse of the data string
			while(p!=NULL){
				if(i==0) carte = strtol(p, NULL, 10);
				else if(i==1) capteur = strtol(p, NULL, 10);
				else if(i==2) val = strtol(p, NULL, 10);
				p = strtok(NULL, ",");
				i++;
			}
						
			//printf("%d %d %d %s\n",carte,capteur,val,addr[carte].unit[capteur]);
			addr[carte].measures[capteur] = val;
			//set data vaidity
			addr[carte].isValid = 1;
				
			nanosleep(&ts,NULL);
		}
	}

}


int main(void)
// main function for coordinator mode
{
		
		for(id_carte=0;id_carte<=255;id_carte++)
		{
			for(id_capteur=0;id_capteur<=255;id_capteur++)
			{
					strcpy(addr[id_carte].unit[id_capteur],"   \0");
			}
			addr[id_carte].isValid = 0;
		}		
		printf("Initialization Finished\n");	
		
		
		// create XBee receiver process
		pthread_t pid;
		pthread_create(&pid, NULL, pthread_XBee, NULL);
		pthread_detach(pid);
		
		//start the web socket on port 8080
		ws_start(8080);

	return 0;
}



