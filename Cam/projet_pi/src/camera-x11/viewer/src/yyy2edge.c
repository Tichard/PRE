/* Raspberry camera viewer

   by Eric Boucharé
   
   20160615: initial release
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

#include <pthread.h>

#include "graphics.h"


/***************************************************************************
 * global parameters
 ***************************************************************************/
int color=1;

/***************************************************************************
 * filtering algorithm
 ***************************************************************************/
#define bounds(m,M,x) ((x)>M ? M : (x)<(m) ? m : (x))

#define RGB16(R,G,B) ((((B) & 0xF8)<<8) | (((G) & 0xFC)<<3) | (((R) & 0xF8)>>3))

//convert a pixel from YUV to RGB 16 (2 bytes)
static uint16_t yuv_to_rgb_16(uint8_t y, uint8_t u, uint8_t v)
{
	int C,D,E,R,G,B;
	
	C=y-16;D=u-128;E=v-128;
	R=bounds(0,255,(298*C+409*E+128)>>8);
	G=bounds(0,255,(298*C-100*D-208*E+128)>>8);
	B=bounds(0,255,(298*C+516*D+128)>>8);

	return RGB16(R,G,B);
}

static void yuv_to_rgb_24(uint8_t *d, uint8_t y, uint8_t u, uint8_t v)
{
	int C,D,E,R,G,B;
	
	C=y-16;D=u-128;E=v-128;
	R=bounds(0,255,(298*C+409*E+128)>>8);
	G=bounds(0,255,(298*C-100*D-208*E+128)>>8);
	B=bounds(0,255,(298*C+516*D+128)>>8);
	
	*d=B;			//blue
	*(d+1)=G;		//green
	*(d+2)=R;		//red
}

static void process_image_yuv420p(Image* img, uint8_t * videoFrame, int width, int height)
{
	uint8_t * data = (uint8_t *) img->xImage->data;
	uint16_t * d16 = (uint16_t*)data;
	int				x, y, xx, yy;
	unsigned char	Y,U,V;
	int				bpl=img->xImage->bytes_per_line;
	int				bpp=img->xImage->bits_per_pixel/8;
	int 			size=width*height;
	
	switch (img->dc->depth) {
	case 16:
		if (!color) {
			for (y = 0; y < height; y++) {
				for (x = 0; x < width; x++) {
					Y=videoFrame[width*y+x];
					d16[width*y+x]=RGB16(Y,Y,Y);
				}
			}
		} else {
			for (yy = 0; yy < height/2; yy++) {
				for (xx = 0; xx < width/2; xx++) {
					//in every loop 4 pixels are processed   
					x=2*xx;
					y=2*yy;
					V = videoFrame[size+(width/2*yy)+(xx)];
					U = videoFrame[size+(size>>2)+(width/2*yy)+(xx)];
		
					Y = videoFrame[width*y+x];
					d16[width*y+x]=yuv_to_rgb_16(Y, U, V);
		
					Y = videoFrame[width*y+(x+1)];
					d16[width*y+x+1]=yuv_to_rgb_16(Y, U, V);
		
					Y = videoFrame[width*(y+1)+x];
					d16[width*(y+1)+x]=yuv_to_rgb_16(Y, U, V);
		
					Y = videoFrame[width*(y+1)+(x+1)];
					d16[width*(y+1)+x+1]=yuv_to_rgb_16(Y, U, V);
				}
			}
		}
		break;
	case 24:
		if (!color) {
			for (y = 0; y < height; y++) {
				for (x = 0; x < width; x++) {
					Y=videoFrame[width*y+x];
					data[(bpl*y)+(bpp*x)]=Y;		//blue
					data[(bpl*y)+(bpp*x)+1]=Y;		//green
					data[(bpl*y)+(bpp*x)+2]=Y;		//red
				}
			}
		} else {
			for (yy = 0; yy < height/2; yy++) {
				for (xx = 0; xx < width/2; xx++) {
					//in every loop 4 pixels are processed   
					x=2*xx;
					y=2*yy;
					V = videoFrame[size+(width/2*yy)+(xx)];
					U = videoFrame[size+(size>>2)+(width/2*yy)+(xx)];
		
					Y = videoFrame[width*y+x];
					yuv_to_rgb_24(data+(bpl*y)+(bpp*x), Y, U, V);
		
					Y = videoFrame[width*y+(x+1)];
					yuv_to_rgb_24(data+(bpl*y)+(bpp*(x+1)), Y, U, V);
		
					Y = videoFrame[width*(y+1)+x];
					yuv_to_rgb_24(data+(bpl*(y+1))+(bpp*x), Y, U, V);
		
					Y = videoFrame[width*(y+1)+(x+1)];
					yuv_to_rgb_24(data+(bpl*(y+1))+(bpp*(x+1)), Y, U, V);
				}
			}
		}
		break;
	default:
		fprintf(stderr,"\nError: Color depth not supported\n");
		exit(EXIT_FAILURE);
		break;
	}	
}


/***************************************************************************
 * main
 ***************************************************************************/
static void usage (FILE *fp, int argc, char **argv)
{
	fprintf (fp,
		"Usage: %s [options]\n\n"
		"Options:\n"
		"-w | --size    <640*480|       Video size\n"
		"                320*240>\n"
		"-h | --help                    Print this message\n"
		"\n",
		argv[0]);
}

//needed to parse command line arguments with getopt_long
static const char short_options [] = "w:h";

//also needed to parse command line arguments with getopt_long
static const struct option
long_options [] = {
	{ "size", required_argument, NULL, 'w' },
	{ "help", no_argument,       NULL, 'h' },
	{ 0, 0, 0, 0 }
};

typedef enum {      
	PIX_FMT_YUV420P,
	PIX_FMT_RGB565,
	PIX_FMT_RGB32,
	PIX_FMT_YUV422,
	PIX_FMT_RAW12
} pix_fmt;

typedef void (*ProcessFunc) (Image *img, uint8_t * frame, int width, int height);

typedef struct {
	int			width;
	int 		height;
	int			factor;
	Image *		img;
	uint8_t *	frame;
	ProcessFunc	process;
} ImgReaderArgs;

void* img_reader_thread(void* p)
{
	ImgReaderArgs *args=(ImgReaderArgs *)p;
	
	Display *		disp = args->img->dc->display;
	Window			w = args->img->dc->drawable;
    XEvent evt;
//    int cpt=0;
    while (1) {
		uint8_t *ptr=args->frame;
		int ret;
		int size=args->width*args->height*args->factor/4;
		while(size) {
			if ((ret = read(STDIN_FILENO, ptr , size)) <= 0) {
				fprintf(stderr, "No more data to be read\n");
				return NULL;
			}
			ptr+=ret;
			size-=ret;
//			fprintf(stderr, "%d bytes to be read of %d : %d\n", size, args->width*args->height*args->factor/4, ret);
		}
		
		args->process(args->img, args->frame, args->width, args->height);

//        fprintf(stderr, "Sending event of type Expose\n");
        memset(&evt, 0, sizeof(evt));
        evt.type = Expose;
        evt.xexpose.window = w;
        evt.xexpose.x = 0;
        evt.xexpose.y = 0;
        evt.xexpose.width = args->width;
        evt.xexpose.height = args->height;
        XSendEvent(disp, w, False, ExposureMask, &evt);
        XFlush(disp);
//        fprintf(stderr, "frame %d\n", ++cpt);
    }
    return NULL;
}

Image * img;
	
static int redraw(Widget *w) {
	image_put(img, 0, 0, 0, 0, image_width(img), image_height(img));
	return 1;
}

static int key_down(Widget*w, unsigned int key, int mod) {
	switch (key) {
	case 'c':
		color=!color;
		break;
	case 'q':
		app_exit();
		break;
	default:
		break;
	}
	return 1;
}

int main (int argc, char * argv[]) 
{
	ImgReaderArgs		ir_args;
	pthread_t			thread;
	int					ret;
	
	uint8_t * 			videoFrame = NULL;
	
	int                 width  = 640;
	int                 height = 480;
	int                 index;
	int                 c;
	pix_fmt             pixel_format = PIX_FMT_YUV420P;
	int					factor = 6;
	
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
				} else {
					sscanf(optarg,"%d*%d",&width,&height);
					fprintf(stderr, "window size %d*%d\n",width,height);
				}
/*				if ((strcmp(optarg,"320*240")!=0)&&(strcmp(optarg,"640*480")!=0))
				{
					fprintf(stderr, "\nError: Window size not supported\n");
					exit(EXIT_FAILURE);
				}*/
				break;

			case 'h':
				usage (stderr, argc, argv);
				exit (EXIT_SUCCESS);

			default:
				usage (stderr, argc, argv);
				exit (EXIT_FAILURE);
		}
	}

	/****************** configure window and display  **********************/
	app_init();
	
	//create the window
	Widget *w=window_new(width, height, "Raspberry camera viewer");
	
	w->redraw = redraw;
	w->key_down = key_down;
	
	if ((img=image_create(w->dc, width, height, True, False)) == NULL) {
		fprintf(stderr, "Error: image_create() failed\n");
		exit(1);
	}
	
	if ((videoFrame = (uint8_t*)malloc (width*height*factor/4)) == NULL) {
		fprintf(stderr, "Error: video frame buffer allocation failed\n");
		exit(1);
	}

	/***********************************************************************/
    ir_args.process = process_image_yuv420p;
	ir_args.img = img;
	ir_args.frame = videoFrame;
	ir_args.width = width;
	ir_args.height = height;
	ir_args.factor = factor;
	
	if((ret = pthread_create (&thread, NULL, img_reader_thread, &ir_args)) != 0) {
		fprintf (stderr, "%s", strerror (ret));
		exit(EXIT_FAILURE);
	}

	app_loop();
    exit (1);
}
