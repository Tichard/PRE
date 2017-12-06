#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/Xatom.h>
#include <X11/extensions/XShm.h>
#include <X11/Xft/Xft.h>


typedef struct {
//	int x, y, w, h;
//	XftColor norm[ColLast];
//	XftColor sel[ColLast];
	Display * 		display;
	Drawable 		drawable;
	Visual *		visual;
	int				depth;
	GC				gc;
	XftFont *		font;
	XftColor		fore;
	XftColor		back;
#if 0
	struct {
		int ascent;
		int descent;
		int height;
		XftFont *xfont;
	}	 			font;
#endif
} DC; /* drawing context */

typedef struct 
{
	DC *			dc;
	Bool            isShared; // MITSHM
	XImage          *xImage;
	Pixmap          sharedPixmap; // None (0L) if unassigned
	XShmSegmentInfo shmInfo;
} Image;

typedef struct _Widget	Widget;

typedef int (*MouseFunc)(Widget*w, int x, int y, int btn, int mod);
typedef int (*KeyFunc)(Widget*w, unsigned int key, int mod);
typedef int (*DrawFunc)(Widget*w);

struct _Widget {
	Window		xid;
	XIC			xic;			// Input context
	DC *		dc;
	int			width;
	int			height;
	DrawFunc	redraw;
	KeyFunc		key_down;
};

void app_init();
void app_loop();
void app_exit();

Widget * window_new(int width, int height, char* title);

DC * dc_new(Display* dpy, Drawable d);
void dc_destroy(DC *dc);

Image* image_create(DC *dc, int width, int height, Bool wantShared,
	Bool wantSharedPixmap);
void image_destroy(Image *img);
int image_put(Image *img, int srcX, int srcY, int dstX, int dstY,
				int width, int height);
int image_width(Image* img);
int image_height(Image* img);

#endif
