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


/***************************************************************************
 * global parameters
 ***************************************************************************/
int color=1;
int chain_out=0;

typedef void (*ProcessFunc)(uint8_t *, int, int);

/* Device Name like /dev/fb */
#define FBNAME	"/dev/fb0"

/* fixed screen information */
struct fb_fix_screeninfo fix_info;

/* configurable screen info */
struct fb_var_screeninfo var_info;

/* The frame buffer memory pointer */
uint8_t *framebuffer;



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
	

	if (absDouble((((double)area) / (perimeter*perimeter) - 0.05) < 0.0005)) return 1; // circle
	else if (absDouble((((double)area) / (perimeter*perimeter) - 0.03) < 0.0005)) return 2; // square
	else return 0;
}


/***************************************************************************
 * image RT processing
 ***************************************************************************/


int im2Obj(uint8_t* videoFrame, int width, int height )
{
	int i,j;
	int size = width*height;
	
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
	for(i=0; i<N;i++){perim[i] = 0; area[i] = 0;}
	
	for(j=1;j<height-2;j++)
	{
		for(i=1;i<width-2;i++)
			{
				val = Y_val[(j)* width + i];
				
				if (val != 0)
				{ 
					
					// check if pixel is on the border
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
							perim[val] += 1; area[val] +=1;
					}
					else
					{
						area[val] +=1;
					}
				}

			
		}
	}

	for(j=1;j<height-2;j++)
	{
		for(i=1;i<width-2;i++)
		{
			val = Y_val[(j)* width + i];
				
			if (val != 0)
			{				
				if (getShape(area[val],perim[val]) == 1) //circle
				{				
					SET_PIXEL32(i,j,RGB32(255,0,255));
				}
				else if (getShape(area[val],perim[val]) == 2) // square
				{				
					SET_PIXEL32(i,j,RGB32(255,0,0));
				}
				else
				{
					SET_PIXEL32(i,j,RGB32(255,255,255));
				}
			}
			else SET_PIXEL32(i,j,RGB32(0,0,0));
		}
	}
	
	// free memory space
	//free(perim);
	//free(area);
	//free(Y_val);
	
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
	int				size;
	int				width  = 640;
	int				height = 480;
	int				factor = 6;
	
	int				fbd;			/* Frame buffer descriptor */

	
	int				 index;
	int				 c;
	
	pix_fmt			pixel_format = PIX_FMT_YUV420P;
	ProcessFunc		proc_func = im2Obj;
	
	
	int				quit=0;	
	
	
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
	uint8_t * videoFrame = (uint8_t*) malloc (width*height*factor/4);
	if (!videoFrame) {
		fprintf(stderr, "could not allocate buffer for video frame (%d bytes required)\n", width*height*2);
		exit (EXIT_FAILURE);
	}
	
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
		proc_func(videoFrame, width, height);
	}
#endif

	/* Release mmap. */
	munmap(framebuffer,0);
	close(fbd);
	
	return EXIT_SUCCESS;
}

	
