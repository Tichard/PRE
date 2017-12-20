/*----------------------------------WEBSOCKET.C----------------------------------*/
/*
 *> [File Name] websocket.c
 *> [Platform] Rasperry PI
 *> [Project] PRE ENIB
 *> [Version] V1.4
 *> [Author] Richard
 *> [Language] C
 *> [Description] websocket API : 
 *> websocket API code 
 */

// Project Header files
#include "web_socket.h"


int ws_start(int port){    
    const char *interface = NULL;
    struct lws_context_creation_info info;
    struct lws_protocols protocol;
    struct lws_context *context;  
    
    // Not using ssl
    const char *cert_path = NULL;
    const char *key_path = NULL;
    
    // no special options
    int opts = 0;


    //* register the signal SIGINT handler */
    struct sigaction act;
    act.sa_handler = INT_HANDLER;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction( SIGINT, &act, 0);

    //* setup websocket protocol */
    protocol.name = "Xbee-data-transmit";
    protocol.callback = ws_service_callback;
    protocol.per_session_data_size=0;
    protocol.rx_buffer_size = 0;

    //* setup websocket context info*/
    memset(&info, 0, sizeof info);
    info.port = port;
    info.iface = interface;
    info.protocols = &protocol;
    info.extensions = NULL; //lws_get_internal_extensions();
    info.ssl_cert_filepath = cert_path;
    info.ssl_private_key_filepath = key_path;
    info.gid = -1;
    info.uid = -1;
    info.options = opts;

    //* create libwebsocket context. */
    context = lws_create_context(&info);
    if (context == NULL) {
        printf("[Main] Websocket context create error.\n");
        return -1;
    }
	
	
	buffer = (char *)malloc(sizeof(char)*(BUFF_SIZE));
	
    printf("[Main] Websocket context create success.\n");

    //* websocket service */
    while ( !destroy_flag ) {
        lws_service(context, 50);
    }
    usleep(10);
    lws_context_destroy(context);

    return 0;
}

int websocket_write_str(struct lws *wsi_in, char *str, int str_size_in) 
// write the string data to the destination wsi
{
    if (str == NULL || wsi_in == NULL)
        return -1;

    int n;
    int len;
    char *out = NULL;

    if (str_size_in < 1) 
        len = strlen(str);
    else
        len = str_size_in;

    out = (char *)malloc(sizeof(char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
    //* setup the buffer*/
    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, str, len );
    //* write out*/
    n = lws_write(wsi_in, out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);
    
    //* free the buffer*/
    free(out);

    return n;
}


static int ws_service_callback(
			struct lws *wsi,
			enum lws_callback_reasons reason, void *user,
			void *in, size_t len)
// callback when data is received
{

    switch (reason) {

        case LWS_CALLBACK_ESTABLISHED:
            printf("[Main Service] Connection established\n");
            break;

        //* If receive a data request from client*/
        case LWS_CALLBACK_RECEIVE:        
        	//printf("[Main Service] Data Requested\n");
        	
        	//create json data
        	if(writeFile(buffer))
        	{ 
        	    //send it     	
        		websocket_write_str(wsi ,buffer, strlen(buffer));
        	}
            break;
            
    case LWS_CALLBACK_CLOSED:
            printf("[Main Service] Client close.\n");
        break;

    default:
            break;
    }

    return 0;
}


int writeFile(char* buffer)
{
	// prep buffer
	memset(buffer,'\0',BUFF_SIZE);
	jwOpen( buffer, BUFF_SIZE, JW_OBJECT, JW_PRETTY );		// start root object
	
	jwObj_array( "cartes" );				// array with elements
	id_carte=1;
	
	while(id_carte<=ID_Board)
	{
		if(addr[id_carte].isValid)
		{
			jwArr_object();					// object in array
			jwObj_int( "id", id_carte);
			jwObj_array( "capteurs" );
									
			id_capteur=1;
			
			while(strcmp(addr[id_carte].unit[id_capteur],"   \0") != 0){
			
				jwArr_object();
				jwObj_int( "id", id_capteur);
				jwObj_string( "unit", addr[id_carte].unit[id_capteur]);
									
				jwObj_double("mesure",(double) addr[id_carte].measures[id_capteur]/10);
				//printf("carte %d capteur %d val %d %s\n",id_carte,id_capteur,addr[id_carte].measures[id_capteur],addr[id_carte].unit[id_capteur]);
				
				jwEnd();
				id_capteur+=1;
			}
								
			jwEnd();
			jwEnd();
			
			
		}
		
		
		// reset data validity
		addr[id_carte].isValid = 0;
		
		id_carte+=1;
	}
	jwEnd();
						
	//end of "anArray" , back to root object
	int err = jwClose(); // close and get error code
	if( err != JWRITE_OK )
	{
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos() );
		
		/*
		// resize buffer data
		char* NEW_BUFF = NULL;
		BUFF_SIZE *= 2;
		NEW_BUFF = (char *)realloc(buffer,sizeof(char)*(BUFF_SIZE));
		
		free(buffer);
		
		if(NEW_BUFF == NULL)
		{	
			// create a new buffer
			NEW_BUFF = (char *)malloc(sizeof(char)*(BUFF_SIZE));
		}
		
		
		buffer = NEW_BUFF;
		*/
		
		
		
		return 0;

	}
	
	
	return 1;
}
