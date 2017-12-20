/* File: fb.c */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>			 /* getopt_long() */
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <signal.h>
#include <libwebsockets.h>


/***************************************************************************
 * global parameters
 ***************************************************************************/
int color=1;
int chain_out=0;

typedef void (*ProcessFunc)(uint8_t *);

/* Device Name like /dev/fb */
#define FBNAME	"/dev/fb0"

/* fixed screen information */
struct fb_fix_screeninfo fix_info;

/* configurable screen info */
struct fb_var_screeninfo var_info;

/* The frame buffer memory pointer */
uint8_t *framebuffer;
uint8_t * videoFrame;

int	width  = 640;
int	height = 480;
int offsetx;
int offsety;
int	factor = 6;
int i,j;
int size;
int	quit=0;	
	
unsigned int BUFF_SIZE = 64;
char * buffer;

int c_disk=0, c_square=0;
uint8_t Nb_disk=0, Nb_square=0;
unsigned short int CAMERA_ON = 0;

static int destroy_flag = 0;

static void INT_HANDLER(int signo) {
    destroy_flag = 1;
}


ProcessFunc	proc_func;

/***************************************************************************
 * utils function
 ***************************************************************************/
#define bounds(m,M,x) ((x)>M ? M : (x)<(m) ? m : (x))

#define LENGTH(x) (sizeof(x) / sizeof((x)[0]))

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))


/*
 * Macro to pack the pixel based on the rgb bit offset.
 * We compute each color value based on bit length
 * and shift it to its corresponding offset in the pixel.
 * each color component is 8 bits long
 *
 * For example: Considering a RGB565, the formula will
 * expand as:-
 * Red len=5, off=11 : Green len=6, off=6 : Blue len=5, off=0
 * pixel_value = ((red >> (8 - 5) << 11)|
 *	   ((green >> (8 - 6) << 6) |
 *	  ((blue >> (8 - 5) << 0)
 */
 
 
#define RGB16(r,g,b) ( \
		(((r) >> (8-var_info.red.length)) << var_info.red.offset) | \
		(((g) >> (8-var_info.green.length)) << var_info.green.offset) | \
		(((b) >> (8-var_info.blue.length)) << var_info.blue.offset) \
)

#define SET_PIXEL16(x,y,color) (((uint16_t*)framebuffer)[(x)+(y)*fix_info.line_length/2]=(color))

#define RGB32(r,g,b) ((uint32_t)( (b) | ((g)<<8) | ((r)<<16) ))

#define SET_PIXEL32(x,y,color) (((uint32_t*)framebuffer)[(x)+(y)*fix_info.line_length/4]=(color))

/* function to a filled rectangle at position (x,y), width w and height h */
void rect_fill(int x,int y, int w, int h, uint32_t color)
{
	int i, j;
	for (i=0;i<w;i++) {
		for (j=0;j<h;j++) {
			SET_PIXEL32(x+i,y+j,color);
		}
	}
}

double absDouble(double x)
{
	if(x<0) return -x;
	else return x;
}

int getShape(int area, int perimeter)
{
	

	if (absDouble(((double)area) / (perimeter*perimeter) - 0.048) < 0.002) return 1; // circle
	else if (absDouble(((double)area) / (perimeter*perimeter) - 0.053) < 0.005) return 2; // square
	else return 0;
}


/***************************************************************************
 * image RT processing
 ***************************************************************************/
 
int imClear()
{
	Nb_disk=0; Nb_square=0;
	// color objects
	for(j=0;j<height;j++)
	{
		for(i=0;i<width;i++)
		{
			
			SET_PIXEL32(i+offsetx,j+offsety,RGB32(0,0,0));
		}
	}
	
	return 0;
}


int imThru(uint8_t* videoFrame)
{
	
	// number of labelled object
	uint8_t label = 0, N = 1;
	

	uint8_t val = 0;
	uint8_t Y_val[size];
	
	int threshold = 90;
	
	if (chain_out)
	{
		int sz=size, l;
		while (sz)
		{
			l=write(STDOUT_FILENO, videoFrame, sz);
			sz-=l;
		}
	}
		
	
	// binarisation and labelisation
	for(j=1;j<height-2;j++)
	{
			for(i=1;i<width-2;i++)
			{	
					
				//val = videoFrame[ (j)   * width + i   ];
				// APPLY FILTER HERE			
								
				if (videoFrame[(j)* width + i] < threshold) val = 255;
				else val = 0;		
				
				
				if (val!=0)
				{
					label = max(Y_val[(j-1)*width+i-1], max(Y_val[(j-1)*width+i], max(Y_val[(j-1)*width+i+1], Y_val[(j)*width+i-1])));
					
					if(label != 0){Y_val[(j)* width + i] = label;}
					else Y_val[(j)* width + i] = N++;
					//Y_val[(j)* width + i] = 1;
					
					
				}
				else Y_val[(j)* width + i] = 0;
				
				//Y_val[(j)* width + i] = val;
		}
	}
	
	//  labelisation correction
	for(j=height-2;j>1;j--)
	{
			for(i=width-2;i>1;i--)
			{					
				if (Y_val[(j)* width + i]!=0)
				{
					label = max(Y_val[(j-1)*width+i-1], max(Y_val[(j-1)*width+i], max(Y_val[(j-1)*width+i+1], Y_val[(j)*width+i-1])));
					label = max(label,max(Y_val[(j+1)*width+i-1], max(Y_val[(j+1)*width+i], max(Y_val[(j+1)*width+i+1], Y_val[(j)*width+i+1]))));
					Y_val[(j)* width + i] = max(label,Y_val[(j)* width + i]);
				}				
		}
	}



	int perim[N];
	int area[N];
	uint8_t disk[N], square[N];
	
	for(i=0; i<N;i++){perim[i] = 0; area[i] = 0;disk[i] = 0; square[i] = 0;}
	
	// count the number of area pixel and border pixel for each label
	
	for(j=1;j<height-2;j++)
	{
		for(i=1;i<width-2;i++)
			{
				val = Y_val[(j)* width + i];
				
				if (val != 0)
				{ 
					
					// check if pixel is on the border
					// 4-connexity
					if (	Y_val[ (j-1)* width+i-1] == 0	||
							Y_val[ (j-1)* width+i  ] == 0 	||
							Y_val[ (j-1)* width+i+1] == 0 	||
							Y_val[ (j)  * width+i-1] == 0 	||
							Y_val[ (j)  * width+i+1] == 0 	||
							Y_val[ (j+1)* width+i-1] == 0 	||
							Y_val[ (j+1)* width+i  ] == 0 	||
							Y_val[ (j+1)* width+i+1] == 0 
						)
					{
							perim[val] += 1; //area[val] +=1;
					}
					else
					{
						area[val] +=1;
					}
				}
			
		}
	}
	
	
	// color objects
	for(j=1;j<height-2;j++)
	{
		for(i=1;i<width-2;i++)
		{
			val = Y_val[(j)* width + i];
				
			if (val != 0)
			{	
				
				if (getShape(area[val],perim[val]) == 1) //circle
				{				
					disk[val] = 1;
				}
				else if (getShape(area[val],perim[val]) == 2) // square
				{				
					square[val] = 1;
				}
				
			}
			val = videoFrame[(j)* width + i];
			SET_PIXEL32(i+offsetx,j+offsety,RGB32(val,val,val));
		}
	}
	
	c_disk=0; c_square=0;
	
	// count the number of disks and squares
	for(i=0;i<N;i++)
	{
		if(disk[i]) c_disk++;
		if(square[i]) c_square++;
	}
	
	Nb_disk = c_disk;
	Nb_square = c_square;
	
	
	return 0;
}


int im2Obj(uint8_t* videoFrame)
{	
	// number of labelled object
	uint8_t label = 0, N = 1;	

	uint8_t val = 0;
	uint8_t Y_val[size];
	
	int threshold = 90;
	
	if (chain_out)
	{
		int sz=size, l;
		while (sz)
		{
			l=write(STDOUT_FILENO, videoFrame, sz);
			sz-=l;
		}
	}
		
	
	// binarisation and labelisation
	for(j=1;j<height-2;j++)
	{
			for(i=1;i<width-2;i++)
			{	
					
				//val = videoFrame[ (j)   * width + i   ];
				// APPLY FILTER HERE			
								
				if (videoFrame[(j)* width + i] < threshold) val = 255;
				else val = 0;		
				
				
				if (val!=0)
				{
					label = max(Y_val[(j-1)*width+i-1], max(Y_val[(j-1)*width+i], max(Y_val[(j-1)*width+i+1], Y_val[(j)*width+i-1])));
					
					if(label != 0){Y_val[(j)* width + i] = label;}
					else Y_val[(j)* width + i] = N++;
					//Y_val[(j)* width + i] = 1;
					
					
				}
				else Y_val[(j)* width + i] = 0;
				
				//Y_val[(j)* width + i] = val;
		}
	}
	
	//  labelisation correction
	for(j=height-2;j>1;j--)
	{
			for(i=width-2;i>1;i--)
			{					
				if (Y_val[(j)* width + i]!=0)
				{
					label = max(Y_val[(j-1)*width+i-1], max(Y_val[(j-1)*width+i], max(Y_val[(j-1)*width+i+1], Y_val[(j)*width+i-1])));
					label = max(label,max(Y_val[(j+1)*width+i-1], max(Y_val[(j+1)*width+i], max(Y_val[(j+1)*width+i+1], Y_val[(j)*width+i+1]))));
					Y_val[(j)* width + i] = max(label,Y_val[(j)* width + i]);
				}				
		}
	}



	int perim[N];
	int area[N];
	uint8_t disk[N], square[N];
	
	for(i=0; i<N;i++){perim[i] = 0; area[i] = 0;disk[i] = 0; square[i] = 0;}
	
	// count the number of area pixel and border pixel for each label
	
	for(j=1;j<height-2;j++)
	{
		for(i=1;i<width-2;i++)
			{
				val = Y_val[(j)* width + i];
				
				if (val != 0)
				{ 
					
					// check if pixel is on the border
					// 4-connexity
					if (	Y_val[ (j-1)* width+i-1] == 0	||
							Y_val[ (j-1)* width+i  ] == 0 	||
							Y_val[ (j-1)* width+i+1] == 0 	||
							Y_val[ (j)  * width+i-1] == 0 	||
							Y_val[ (j)  * width+i+1] == 0 	||
							Y_val[ (j+1)* width+i-1] == 0 	||
							Y_val[ (j+1)* width+i  ] == 0 	||
							Y_val[ (j+1)* width+i+1] == 0 
						)
					{
							perim[val] += 1; //area[val] +=1;
					}
					else
					{
						area[val] +=1;
					}
				}
			
		}
	}
	

	
	// color objects
	for(j=1;j<height-2;j++)
	{
		for(i=1;i<width-2;i++)
		{
			val = Y_val[(j)* width + i];
				
			if (val != 0)
			{	
				
				if (getShape(area[val],perim[val]) == 1) //circle
				{				
					SET_PIXEL32(i+offsetx,j+offsety,RGB32(255,0,255));
					disk[val] = 1;
				}
				else if (getShape(area[val],perim[val]) == 2) // square
				{				
					SET_PIXEL32(i+offsetx,j+offsety,RGB32(255,0,0));
					square[val] = 1;
				}
				else
				{
					SET_PIXEL32(i+offsetx,j+offsety,RGB32(255,255,255));
				}
				
			}
			else SET_PIXEL32(i+offsetx,j+offsety,RGB32(0,0,0));
		}
	}
	
	c_disk=0; c_square=0;
	
	// count the number of disks and squares
	for(i=0;i<N;i++)
	{
		if(disk[i]) c_disk++;
		if(square[i]) c_square++;
	}
	
	Nb_disk = c_disk;
	Nb_square = c_square;
	
	
	return 0;
}



/***************************************************************************
 * server & pid
 ***************************************************************************/

int websocket_write_str(struct lws *wsi_in, char *str, int str_size_in) 
// write the string data to the destination wsi
{
    if (str == NULL || wsi_in == NULL)
        return -1;

    int n;
    int len;
    unsigned char *out = NULL;

    if (str_size_in < 1) 
        len = strlen(str);
    else
        len = str_size_in;
	
	
    out = (char *)malloc(sizeof(char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
    //* setup the buffer*/
    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, str, len );
    //* write out*/
    n = lws_write(wsi_in, out + LWS_SEND_BUFFER_PRE_PADDING, len,LWS_WRITE_TEXT);
    
    //* free the buffer*/
    free(out);

    return n;
}


static void *pthread_Cam()
{

	while (1) {
		uint8_t *ptr=videoFrame;
		int ret;
		int size=width*height*factor/4;
		while(size) {
			if ((ret = read(STDIN_FILENO, ptr , size)) <= 0) {
				fprintf(stderr, "No more data to be read\n");
				quit = 1;
				break;
			}
			ptr+=ret;
			size-=ret;
		}
		
		if (quit) break;
		
		//proc_func(videoFrame, width, height);
		if(CAMERA_ON) proc_func(videoFrame);
	}

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
        	if (!strcmp((char*)in,"CAMERA_ON")){CAMERA_ON = 1;}
        	else if (!strcmp((char*)in,"CAMERA_OFF"))
        		{CAMERA_ON = 0; imClear();}
        	
        	else if (!strcmp((char*)in,"VIDTHRU"))
        		{proc_func = (ProcessFunc)imThru; }
        	
        	else if (!strcmp((char*)in,"VIDOBJ"))
        		{proc_func = (ProcessFunc)im2Obj;}
        	
        	else if (!strcmp((char*)in,"COUNT")){
        		sprintf(buffer, "%d pièces rondes et %d\n pièces carrées",Nb_disk,Nb_square);
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
    protocol.name = "Cam-WebSocket";
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

/***************************************************************************
 * main
 ***************************************************************************/
static void usage (FILE *fp, int argc, char **argv)
{
	fprintf (fp,
		"Usage: %s [options]\n\n"
		"Options:\n"
		"-w | --size	<640*480|	   Video size\n"
		"				320*240>\n"
		"-c							 Show colored image\n"
		"-o							 Chain the incoming data to standard output\n"
		"-h | --help					Print this message\n"
		"\n",
		argv[0]);
}

//needed to parse command line arguments with getopt_long
static const char short_options [] = "w:h:c:o";

//also needed to parse command line arguments with getopt_long
static const struct option
long_options [] = {
	{ "size", required_argument, NULL, 'w' },
	{ "color", no_argument,	  NULL, 'c' },
	{ "output", no_argument,	 NULL, 'o' },
	{ "help", no_argument,	   NULL, 'h' },
	{ 0, 0, 0, 0 }
};

typedef enum {	  
	PIX_FMT_YUV420P,
	PIX_FMT_RGB565,
	PIX_FMT_RGB32,
	PIX_FMT_YUV422,
	PIX_FMT_RAW12
} pix_fmt;


typedef struct {
	int			width;
	int 		height;
	int			factor;
	uint8_t *	frame;
	ProcessFunc	process;
} ImgReaderArgs;

int main(int argc, char *argv[])
{

	int	fbd;			/* Frame buffer descriptor */
	int index;
	int c;	

	for (;;) {
		c = getopt_long (argc, argv, short_options, long_options, &index);

		if (-1 == c)
			break; //no more arguments

		switch (c) 
		{
			case 0: // getopt_long() flag
				break;

			case 'w':
				if (strcmp(optarg,"640*480")==0) {
					fprintf(stderr, "window size 640*480\n");
					width=640;
					height=480;
				} else if (strcmp(optarg,"320*240")==0) {
					fprintf(stderr, "window size 320*240\n");
					width=320;
					height=240;
				} else if (strcmp(optarg,"960*720")==0) {
					fprintf(stderr, "window size 960*720\n");
					width=960;
					height=720;
				} else {
					sscanf(optarg,"%d*%d",&width,&height);
					fprintf(stderr, "window size %d*%d\n",width,height);
				}
				break;

			case 'c':
				color = 1;
				break;
				
			case 'o':
				chain_out = 1;
				break;
				
			case 'h':
				usage (stderr, argc, argv);
				exit (EXIT_SUCCESS);

			default:
				usage (stderr, argc, argv);
				exit (EXIT_FAILURE);
		}
	}

	
	size = width*height;
	
	/* Open the framebuffer device in read write */
	fbd = open(FBNAME, O_RDWR);
	if (fbd < 0) {
		fprintf(stderr, "Unable to open %s.\n", FBNAME);
		return EXIT_FAILURE;
	}

	/* Do Ioctl. Retrieve fixed screen info. */
	if (ioctl(fbd, FBIOGET_FSCREENINFO, &fix_info) < 0) {
		fprintf(stderr, "get fixed screen info failed: %s\n",
			strerror(errno));
		close(fbd);
		return EXIT_FAILURE;
	}

	/* Do Ioctl. Get the variable screen info. */
	if (ioctl(fbd, FBIOGET_VSCREENINFO, &var_info) < 0) {
		fprintf(stderr, "Unable to retrieve variable screen info: %s\n",
			strerror(errno));
		close(fbd);
		return EXIT_FAILURE;
	}


	/* Print some screen info currently available */
	fprintf(stderr, "Screen resolution: (%dx%d)\n",var_info.xres,var_info.yres);
	fprintf(stderr, "x offset, y offset : %d, %d\n",var_info.xoffset,var_info.yoffset);
	fprintf(stderr, "Line width in bytes %d\n", fix_info.line_length);
	fprintf(stderr, "bits per pixel : %d\n", var_info.bits_per_pixel);
	fprintf(stderr, "Red: length %d bits, offset %d\n",var_info.red.length,var_info.red.offset);
	fprintf(stderr, "Green: length %d bits, offset %d\n",var_info.red.length, var_info.green.offset);
	fprintf(stderr, "Blue: length %d bits, offset %d\n",var_info.red.length,var_info.blue.offset);
	/* Calculate the size to mmap */
	size=fix_info.line_length * var_info.yres;
	
	//upper-left corner
	offsetx = var_info.xres-width;
	offsety = 0;

	/* Now mmap the framebuffer. */
	framebuffer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fbd,0);
	if (framebuffer == NULL) {
		fprintf(stderr, "mmap failed:\n");
		close(fbd);
		return EXIT_FAILURE;
	}
	

	fprintf(stderr, "framebuffer mmap address=%p\n", framebuffer);
	fprintf(stderr, "framebuffer size=%d bytes\n", size);

#if 0
	rect_fill(100,200,300,150, RGB32(0, 0, 0xFF));

#else	
	videoFrame = (uint8_t*) malloc (width*height*factor/4);
	if (!videoFrame) {
		fprintf(stderr, "could not allocate buffer for video frame (%d bytes required)\n", width*height*2);
		exit (EXIT_FAILURE);
	}
	
	// set to pass-through video stream
	proc_func = (ProcessFunc)imThru;
	
	// create Cam process receiver process
		pthread_t pid;
		pthread_create(&pid, NULL, pthread_Cam, NULL);
		pthread_detach(pid);
		
		//start the web socket on port 8181
		ws_start(8181);
	
#endif

	/* Release mmap. */
	munmap(framebuffer,0);
	close(fbd);
	
	return EXIT_SUCCESS;
}



	
