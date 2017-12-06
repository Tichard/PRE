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
int filter = 0;
int chain_out = 0;
/***************************************************************************
 * filtering algorithm
 ***************************************************************************/
static void process_image_yuv420p(Image* img, uint8_t * Y, int width, int height)
{
	uint8_t * data = (uint8_t *)img->xImage->data;
	uint16_t * d16 = (uint16_t*)data;
	int				x, y;
	int16_t			a, b;
	uint8_t			c;
	int				bpl=img->xImage->bytes_per_line;
	int				bpp=img->xImage->bits_per_pixel/8;
	
	switch (img->dc->depth) {
	case 16:
	
		/* A COMPLETER */
		
		break;
		
	case 24:
	
		/* A COMPLETER */
		
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
		"-o                             Chain incomming data to standard output\n"
		"-h | --help                    Print this message\n"
		"\n",
		argv[0]);
}

//needed to parse command line arguments with getopt_long
static const char short_options [] = "w:h:o";

//also needed to parse command line arguments with getopt_long
static const struct option
long_options [] = {
	{ "size", required_argument, NULL, 'w' },
	{ "help", no_argument,       NULL, 'h' },
	{ "output", no_argument,     NULL, 'o' },
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
    while (1) {
		uint8_t *ptr=args->frame;
		int ret;
		int size=args->width*args->height;
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
	case '0':
		filter=0;
		break;
	case 'o':
		chain_out = !chain_out;
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
	
	if ((videoFrame = (uint8_t*)malloc(width*height)) == NULL) {
		fprintf(stderr, "Error: video frame buffer allocation failed\n");
		exit(1);
	}

	/***********************************************************************/
    ir_args.process = process_image_yuv420p;
	ir_args.img = img;
	ir_args.frame = videoFrame;
	ir_args.width = width;
	ir_args.height = height;
	
	if((ret = pthread_create (&thread, NULL, img_reader_thread, &ir_args)) != 0) {
		fprintf (stderr, "%s", strerror (ret));
		exit(EXIT_FAILURE);
	}

	app_loop();
    exit (1);
}
