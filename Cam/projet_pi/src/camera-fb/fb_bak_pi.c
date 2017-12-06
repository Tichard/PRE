/* File: fb.c */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
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
 *       ((green >> (8 - 6) << 6) |
 *      ((blue >> (8 - 5) << 0)
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

int abs(int x)
{
	if(x<0) return -x;
	else return x;
}
/***************************************************************************
 * decoding stuff
 ***************************************************************************/
#define bounds(m,M,x) ((x)>M ? M : (x)<(m) ? m : (x))

int detec_contour(uint8_t* videoFrame, int width, int height ){
	int i,j;
	int size = width*height;
	
	if (chain_out) {
		int sz=size, l;
		while (sz) {
			l=write(STDOUT_FILENO, videoFrame, sz);
			sz-=l;
		}
	}
	uint32_t l1_gauss,l2_gauss,l3_gauss;
        int32_t laplacien, l1_lap, l2_lap, l3_lap , Gx, Gy;
        int max_grad = 1;
        float val;
	uint32_t Y_val [size]; uint32_t Grad [size];
	for(i=0;i<width;i++){
			for(j=0;j<height;j++){
				Y_val[j*width+i] = videoFrame[j*width+i];
		}
	}
        
        // Filtre Gaussien
        // Sigma = 1.4 matrice extraite de wikipedia
	for (i = 2; i< width-3;i++){
		for (j = 2; j < height-3; j++){
                        l1_gauss = Y_val[(j-1)*width+i-1] + 2*Y_val[(j-1)*width+i] + Y_val[(j-1)*width+i+1];
                        l2_gauss = 2*Y_val[(j)*width+i-1] + 4*Y_val[(j)*width+i]   + 2*Y_val[(j)*width+i+1];
                        l3_gauss = Y_val[(j+1)*width+i-1] + 2*Y_val[(j+1)*width+i] + Y_val[(j+1)*width+i+1];
                        Y_val[j*width+i] = (uint32_t) (l1_gauss+l2_gauss+l3_gauss)/16;
                }
        }

        // Laplacien
        float lambda = 0.4;
        for (i = 1; i< width-2;i++){
                for (j = 1; j < height-1; j++){
			l1_lap = -Y_val[(j-1)*width+i-1]  -   Y_val[(j-1)*width+i] - Y_val[(j-1)*width+i+1];
                        l2_lap = -Y_val[(j)*width+i-1]    + 8*Y_val[(j)*width+i]   - Y_val[(j)*width+i+1];
                        l3_lap = -Y_val[(j+1)*width+i-1]  -   Y_val[(j+1)*width+i] - Y_val[(j+1)*width+i+1];
                        laplacien = l1_lap + l2_lap + l3_lap;
                        Y_val[j*width+i] = abs(Y_val[j*width+i]-lambda*laplacien);
		}
	}
        
        
        
    // Gradient d'intensité
	max_grad = 0;

        for (i = 1; i< width-1;i++){
                for (j = 1; j < height-1; j++){
                        Gx = -Y_val[j*width+i-1]   +Y_val[j*width+i+1];
                        Gy = -Y_val[(j-1)*width+i] +Y_val[(j+1)*width+i];
                        Grad[j*width+i] = abs(Gx) + abs(Gy);//(uint32_t) sqrt(Gx^2 + Gy^2);
                        //SET_PIXEL32(i,j,RGB32(Grad[j*width+i],Grad[j*width+i],Grad[j*width+i]));
                        if (abs(Grad[j*width+i]) > max_grad) max_grad = abs(Grad[j*width+i]);                        
		}
	}
	
	// Normalisation du gradient
	for (i = 1; i< width-2;i++){
		for (j = 1; j < height-1; j++){
			val = abs(Grad[j*width+i])*255/max_grad;
                        if (val < 10) val = 0;
			else val = 255;
                        SET_PIXEL32(i,j,RGB32((uint32_t)val,(uint32_t)val,(uint32_t)val));
		}
	}
	
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
		"-w | --size    <640*480|       Video size\n"
		"                320*240>\n"
		"-c                             Show colored image\n"
		"-o                             Chain the incoming data to standard output\n"
		"-h | --help                    Print this message\n"
		"\n",
		argv[0]);
}

//needed to parse command line arguments with getopt_long
static const char short_options [] = "w:h:c:o";

//also needed to parse command line arguments with getopt_long
static const struct option
long_options [] = {
	{ "size", required_argument, NULL, 'w' },
	{ "color", no_argument,      NULL, 'c' },
	{ "output", no_argument,     NULL, 'o' },
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


typedef struct {
	int			width;
	int 		height;
	int			factor;
	uint8_t *	frame;
	ProcessFunc	process;
} ImgReaderArgs;

int main(int argc, char *argv[])
{
    int size;

	int					fbd;			/* Frame buffer descriptor */

	int                 width  = 640;
	int                 height = 480;
	int                 index;
	int                 c;
	pix_fmt             pixel_format = PIX_FMT_YUV420P;
	ProcessFunc			proc_func=detec_contour;
	int					factor = 6;
	
	int					quit=0;
	
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

