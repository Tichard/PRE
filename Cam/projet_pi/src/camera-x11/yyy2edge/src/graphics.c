#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <langinfo.h>
#include <locale.h>

#include "graphics.h"

/***************************************************************************
 * Drawing Context object handling
 ***************************************************************************/
#if 0
XftColor getcolor(const char *colstr) {
	XftColor color;

	if(!XftColorAllocName(dpy, DefaultVisual(dpy, screen), DefaultColormap(dpy, screen), colstr, &color))
		fprinf("error, cannot allocate color '%s'\n", colstr);
		exit(1);

	return color;
}

void
die(const char *errstr, ...) {
	va_list ap;

	va_start(ap, errstr);
	vfprintf(stderr, errstr, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void initfont(const char *fontstr) {

	if(!(dc.font.xfont = XftFontOpenName(dpy,screen,fontstr))
	&& !(dc.font.xfont = XftFontOpenName(dpy,screen,"fixed")))
		die("error, cannot load font: '%s'\n", fontstr);

	dc.font.ascent = dc.font.xfont->ascent;
	dc.font.descent = dc.font.xfont->descent;
	dc.font.height = dc.font.ascent + dc.font.descent;
}

int
textnw(const char *text, unsigned int len) {
	XGlyphInfo ext;
	XftTextExtentsUtf8(dpy, dc.font.xfont, (XftChar8 *) text, len, &ext);
	return ext.xOff;
}

void
drawtext(const char *text, XftColor col[ColLast], Bool invert) {
	char buf[256];
	int i, x, y, h, len, olen;
	XftDraw *d;

	XSetForeground(dpy, dc.gc, col[invert ? ColFG : ColBG].pixel);
	XFillRectangle(dpy, dc.drawable, dc.gc, dc.x, dc.y, dc.w, dc.h);
	if(!text)
		return;
	olen = strlen(text);
	h = dc.font.ascent + dc.font.descent;
	y = dc.y + (dc.h / 2) - (h / 2) + dc.font.ascent;
	x = dc.x + (h / 2);
	/* shorten text if necessary */
	for(len = MIN(olen, sizeof buf); len && textnw(text, len) > dc.w - h; len--);
	if(!len)
		return;
	memcpy(buf, text, len);
	if(len < olen)
		for(i = len; i && i > len - 3; buf[--i] = '.');

	d = XftDrawCreate(dpy, dc.drawable, DefaultVisual(dpy, screen), DefaultColormap(dpy,screen));

	XftDrawStringUtf8(d, &col[invert ? ColBG : ColFG], dc.font.xfont, x, y, (XftChar8 *) buf, len);
	XftDrawDestroy(d);
}
#endif

DC * dc_new(Display* dpy, Drawable d)
{
	DC *dc=(DC*)malloc(sizeof(DC));
	
	XGCValues          gcValues;
	unsigned long      gcValuesMask;
	XWindowAttributes  windowAttributes;

	if (!dc) return NULL;
	
	dc->display = dpy;
	dc->drawable = d;
	
	gcValues.function = GXcopy;
	gcValuesMask = GCFunction;
	dc->gc = XCreateGC(dc->display, dc->drawable, gcValuesMask, &gcValues);

	XGetWindowAttributes(dc->display, dc->drawable, &windowAttributes);

	dc->visual = windowAttributes.visual;
	dc->depth = windowAttributes.depth;

	return dc;
}

void dc_destroy(DC *dc)
{
	if (dc->display != NULL) 
	{
		XFreeGC(dc->display, dc->gc);
	}
	
	free(dc);
}

void dc_set_font(DC* dc, char* fontstr)
{
	if(!(dc->font = XftFontOpenName(dc->display, DefaultScreen(dc->display), fontstr))
		&& !(dc->font = XftFontOpenName(dc->display, DefaultScreen(dc->display), "fixed"))) {
		fprintf(stderr, "error, cannot load font: '%s'\n", fontstr);
	}

/*	dc->font.ascent = dc->font.xfont->ascent;
	dc->font.descent = dc->font.xfont->descent;
	dc->font.height = dc->font.ascent + dc->font.descent;*/
}

/*
void drawtext(DC* dc, const char *text, XftColor col[ColLast], Bool invert) {
	char buf[256];
	int i, x, y, h, len, olen;
	XftDraw *d;

//	XSetForeground(dpy, dc.gc, col[invert ? ColFG : ColBG].pixel);
//	XFillRectangle(dpy, dc.drawable, dc.gc, dc.x, dc.y, dc.w, dc.h);
	if(!text) return;
	
	olen = strlen(text);
	h = dc->font.ascent + dc->font.descent;
	y = dc.y + (dc.h / 2) - (h / 2) + dc.font.ascent;
	x = dc.x + (h / 2);
	// shorten text if necessary
	for(len = MIN(olen, sizeof buf); len && textnw(text, len) > dc.w - h; len--);
	if(!len)
		return;
	memcpy(buf, text, len);
	if(len < olen)
		for(i = len; i && i > len - 3; buf[--i] = '.');

	d = XftDrawCreate(dpy, dc.drawable, DefaultVisual(dpy, screen), DefaultColormap(dpy,screen));

	XftDrawStringUtf8(d, &col[invert ? ColBG : ColFG], dc.font.xfont, x, y, (XftChar8 *) buf, len);
	XftDrawDestroy(d);
}
*/
/***************************************************************************
 * Image object handling
 ***************************************************************************/
int image_width(Image* img);
int image_height(Image* img);

Image* image_create(DC *dc, int width, int height, Bool wantShared,
				Bool wantSharedPixmap)
{
	Image *img=(Image*)malloc(sizeof(Image));
	
	if (!img) return NULL;
	
	img->dc = dc;
	img->isShared = wantShared && XShmQueryExtension(dc->display);

//	errno = 0;
	img->xImage = NULL;
	img->sharedPixmap = None;
	if (img->isShared) {
		img->shmInfo.shmid = -1;
		img->shmInfo.shmaddr = NULL;
		if ((
			img->xImage = XShmCreateImage(dc->display, dc->visual, 
			dc->depth, ZPixmap, NULL, &(img->shmInfo), width, height)
			) == NULL) {
			free(img);
			return NULL;
		}
		if ((img->shmInfo.shmid = shmget(IPC_PRIVATE,
			img->xImage->bytes_per_line * img->xImage->height, 
			IPC_CREAT | 0777)) < 0) {
			// Create segment
			free(img);
			return NULL;
		}
		if ((img->shmInfo.shmaddr = (char *) shmat(img->shmInfo.shmid, 0, 0)) < 0) {
			// We attach
			img->shmInfo.shmaddr = NULL;
			free(img);
			return NULL;
		}
		img->xImage->data = img->shmInfo.shmaddr;
		img->shmInfo.readOnly = False;
		if (!XShmAttach(dc->display, &(img->shmInfo))) {
		 // X attaches
			free(img);
			return NULL;
		}
		if (wantSharedPixmap && 
			(XShmPixmapFormat(dc->display) == ZPixmap)) {
			if ((img->sharedPixmap = XShmCreatePixmap(dc->display, dc->drawable, 
				img->shmInfo.shmaddr, &(img->shmInfo), width, height, dc->depth))
				== None) {
				free(img);
				return NULL;
			}
		}
	} else {
		if ((img->xImage = XCreateImage(dc->display, dc->visual,
			dc->depth, ZPixmap, 0, NULL, width, height, 16, 0)) == NULL) {
			free(img);
			return NULL;
		}

		img->xImage->data = 
			(char *)malloc(img->xImage->bytes_per_line * img->xImage->height);

		if (img->xImage->data == NULL) {
			free(img);
			return NULL;
		}
	}
	return img;
}

void image_destroy(Image *img)
{
	if (img->xImage == NULL) return; // Nothing to do

	if (img->isShared) {
		if (img->shmInfo.shmid >= 0) {
			XShmDetach(img->dc->display, &(img->shmInfo)); // X detaches
			shmdt(img->shmInfo.shmaddr); // We detach
			img->shmInfo.shmaddr = NULL;
			shmctl(img->shmInfo.shmid, IPC_RMID, 0); // Destroy segment
			img->shmInfo.shmid = -1;
		}
	} else {
		if (img->xImage->data != NULL) {
			free(img->xImage->data);
		}
	}

	img->xImage->data = NULL;

	XDestroyImage(img->xImage);

	img->xImage = NULL;

	if (img->sharedPixmap != None) {
		XFreePixmap(img->dc->display, img->sharedPixmap);
		img->sharedPixmap = None;
	}
	
	free(img);
}

int image_put (Image *img, int srcX, int srcY, int dstX, int dstY,
				int width, int height) {

	if (img->xImage == NULL) return (-1);

	if (width < 0) width = image_width(img);
	if (height < 0) height = image_height(img);

	if (img->isShared) {
		XShmPutImage(img->dc->display, img->dc->drawable, img->dc->gc, 
			img->xImage, srcX, srcY, dstX, dstY, width, height, False);
	} else {
		XPutImage(img->dc->display, img->dc->drawable, img->dc->gc, 
			img->xImage, srcX, srcY, dstX, dstY, width, height);
	}

	return 0;
}

int image_width(Image* img)  
{
	return ((img->xImage != NULL) ? img->xImage->width : 0);
}

int image_height(Image* img) 
{
	return ((img->xImage != NULL) ? img->xImage->height : 0);
}

/***************************************************************************
 * Image object handling
 ***************************************************************************/
/*static char *ByteOrderName(int byteOrder)
{
	switch (byteOrder) 
	{
		case LSBFirst: return ("LSBFirst");
		case MSBFirst: return ("MSBFirst");
		default:       return ("?");
	} 
}

static char *VisualClassName(int visualClass)
{
	switch (visualClass) 
	{
		case StaticGray:  return ("StaticGray");
		case GrayScale:   return ("GrayScale");
		case StaticColor: return ("StaticColor");
		case PseudoColor: return ("PseudoColor");
		case TrueColor:   return ("TrueColor");
		case DirectColor: return ("DirectColor");
		default:          return ("?");
	} 
}
*/
/************* Show info about display, window and image *******************/

/*	fprintf(stderr,"\nDisplay:\n");
	fprintf(stderr,"Image byte order = %s\n", ByteOrderName(ImageByteOrder(display)));
	fprintf(stderr,"Bitmap unit      = %i\n", BitmapUnit(display));
	fprintf(stderr,"Bitmap bit order = %s\n", ByteOrderName(BitmapBitOrder(display)));
	fprintf(stderr,"Bitmap pad       = %i\n", BitmapPad(display));

	fprintf(stderr,"Image byte order = %s\n", ByteOrderName((img->xImage)->byte_order));
	fprintf(stderr,"Bitmap unit      = %i\n", img->xImage->bitmap_unit);
	fprintf(stderr,"Bitmap bit order = %s\n", ByteOrderName(img->xImage->bitmap_bit_order));
	fprintf(stderr,"Bitmap pad       = %i\n", img->xImage->bitmap_pad);
	fprintf(stderr,"Depth            = %i\n", img->xImage->depth);
	fprintf(stderr,"Red mask         = 0x%08lx\n", img->xImage->red_mask);
	fprintf(stderr,"Green mask       = 0x%08lx\n", img->xImage->green_mask);
	fprintf(stderr,"Blue mask        = 0x%08lx\n", img->xImage->blue_mask);
	fprintf(stderr,"Bits per pixel   = %i\n", img->xImage->bits_per_pixel);
	fprintf(stderr,"Bytes per line   = %i\n", img->xImage->bytes_per_line);
	fprintf(stderr,"IsShared         = %s\n", img->isShared ? "True" : "False");
	//fprintf(stderr,"HasSharedPixmap  = %s\n", img->HasSharedPixmap() ? "True" : "False");
*/

Display *			display;	/* X11 Display */
int					screenNumber;
Atom				wm_del_window_atom;
Screen *			screen;
XContext			xctx;
XIM xim;
int encoding=0;

static int			app_quit = 0;

void app_init()
{
	setlocale(LC_CTYPE, "");
	XSetLocaleModifiers("");
	
	char *enc_str=nl_langinfo(CODESET); 
	fprintf(stderr, "%s\n", enc_str);
	if (strcmp(enc_str, "ISO-8859-1")==0) {
		fprintf(stderr, "Encoding is ISO-8859-1\n");
		encoding=0;
	} else {
		fprintf(stderr, "Encoding is UTF8\n");
		encoding=1;
	}
	
	if (!XInitThreads()) {
		fprintf(stderr, "Xlib not thread safe\n");
		exit(1);
	}
	
	/* open connection to X display */
	if ((display = XOpenDisplay(NULL)) == NULL) 
	{ 
		fprintf(stderr, "Error: fallo XOpenDisplay() \n");
		exit(1);
	}
	
	/* input methods */
	if((xim = XOpenIM(display, NULL, NULL, NULL)) == NULL) {
		XSetLocaleModifiers("@im=local");
		if((xim =  XOpenIM(display, NULL, NULL, NULL)) == NULL) {
			XSetLocaleModifiers("@im=");
			if((xim = XOpenIM(display, NULL, NULL, NULL)) == NULL) {
				fprintf(stderr, "XOpenIM failed. Could not open input device.\n");
			}
		}
	}
	
	//get default display number
	screenNumber = DefaultScreen(display);
	//associate screen with the default display
	screen = XScreenOfDisplay(display, screenNumber);

	wm_del_window_atom = XInternAtom(display, "WM_DELETE_WINDOW", False);
	
	// setup a new context for app
	xctx = XUniqueContext();
}

void app_exit()
{
	app_quit = 1;
}

#define	EXPOSE_CACHE_SIZE	32

void app_loop()
{
	XEvent				event;
	XRectangle			clipmask[EXPOSE_CACHE_SIZE];
	int					exposec = 0;

	Widget* widget = NULL;
	
	int len;
	Status status;
	char buf[15];
	KeySym keysym;

    while(!app_quit) {
		XNextEvent(display, &event); //refresh the picture
		if(XFilterEvent(&event, None)) continue;
		if (event.type!=UnmapNotify && event.type!=DestroyNotify) {
			//	get the widget object the event must be sent to
			XFindContext(event.xany.display, event.xany.window, xctx,
				(XPointer*)&widget);
		
			switch (event.type) {
			case KeyPress:
				len = XmbLookupString(widget->xic, &event.xkey, buf, sizeof(buf), &keysym, &status);
				buf[len]=0;
				fprintf(stderr, "KeyPress: len=%d, buf[]=%s, ksym=0x%x\n", len, buf, (unsigned)keysym);
				switch(status) {
				case XBufferOverflow:
					fprintf(stderr, "XLookupString: buffer too short_n");
					break;
				case XLookupNone:
					fprintf(stderr, "XLookupString: no lookup could be done\n");
					break;
				case XLookupChars:
					fprintf(stderr, "XLookupString: lookup for string done, keysym not changed\n");
					break;
				
				case XLookupKeySym:
					fprintf(stderr, "XLookupString: lookup for keysym done, not string\n");
					break;
				case XLookupBoth:
					fprintf(stderr, "XLookupString: lookup for string and keysym done\n");
					break;
				}
//				length = XLookupString(&event.xkey,buffer,14,&keysym,0);
				if (len && widget->key_down) widget->key_down(widget, (int)buf[0], 0);
				break;
				
			case ButtonPress:
/*				Point p;
				p.x = event.xbutton.x;
				p.y = event.xbutton.y;
*/
				break;
			case ButtonRelease:
/*				Point p;
				p.x = event.xbutton.x;
				p.y = event.xbutton.y;
*/				
				break;
			case MotionNotify:
/*				Point p;
				p.x = event.xmotion.x;
				p.y = event.xmotion.y;
*/
				break;
			case EnterNotify:
				break;
				
			case LeaveNotify:
				break;
				
			case FocusIn:
				break;
				
			case FocusOut:
				break;
				
			case ConfigureNotify:
				break;
			
			case Expose:
				clipmask[exposec].x		= event.xexpose.x;
				clipmask[exposec].y		= event.xexpose.y;
				clipmask[exposec].width	= event.xexpose.width;
				clipmask[exposec].height= event.xexpose.height;
				exposec++;
				
//				fprintf(stderr, "Expose evt : %d\n", exposec);

				if(!event.xexpose.count || exposec == EXPOSE_CACHE_SIZE) {
					XSetClipRectangles(display, widget->dc->gc, 0, 0,
						clipmask, exposec, Unsorted);
	
					exposec=0;
					
					if (widget->redraw) widget->redraw(widget);

					clipmask[0].x		= 0;
					clipmask[0].y		= 0;
					clipmask[0].width	= widget->width;
					clipmask[0].height	= widget->height;

					XSetClipRectangles(display, widget->dc->gc, 0, 0, clipmask, 1, 
						Unsorted);
				}
				break;
				
			case ClientMessage:
				if ((Atom)(event.xclient.data.l[0]) == wm_del_window_atom) {
					app_quit=1;
					break;
				}
			
			case KeymapNotify:
				break;
				
			default:
				break;
			}
		}
    }

}

Widget * window_new(int width, int height, char* title)
{
//	XWindowAttributes	windowAttributes;
	
	Widget *w = (Widget*)malloc(sizeof(Widget));
	if (!w) {
		fprintf(stderr, "window_new: allocation failed\n");
		exit(EXIT_FAILURE);
	}
	memset(w,0,sizeof(Widget));
	
	//create the window
	w->xid = XCreateSimpleWindow(
		display,
		RootWindowOfScreen(screen),
		0, // x
		0, // y
		width, // width
		height, // height
		0,                          // border width
		BlackPixelOfScreen(screen), // border
		BlackPixelOfScreen(screen)  // background
	);

	w->width = width;
	w->height = height;
	
	// bind the window to object
	XSaveContext(display, w->xid, xctx, (XPointer)w);
	
	if ((w->xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, w->xid,
		XNFocusWindow, w->xid, NULL))==NULL) {
		fprintf(stderr, "XCreateIC failed. Could not obtain input method.\n");
	}
	
	XSetIconName(display, w->xid, title);
	XSetWMProtocols(display, w->xid, &wm_del_window_atom, 1);
	XStoreName(display, w->xid, title);
	XSelectInput(display, w->xid, StructureNotifyMask|ExposureMask|KeyPressMask|ButtonPressMask);
	
	// create a graphic context
	if ((w->dc = dc_new(display, w->xid)) == NULL) {
		fprintf(stderr, "Error: dc_new() failed\n");
		exit(1);
	}
	
	// map the window
	XMapWindow(display, w->xid);
/*	
	XGetWindowAttributes(display, w->xid, &windowAttributes);
	fprintf(stderr,"\nWindow:\n");
	fprintf(stderr,"Depth            = %i\n", windowAttributes.depth);
	fprintf(stderr,"Visual ID        = 0x%02x\n", windowAttributes.visual->visualid);
	fprintf(stderr,"Red mask         = 0x%08lx\n", windowAttributes.visual->red_mask);
	fprintf(stderr,"Green mask       = 0x%08lx\n", windowAttributes.visual->green_mask);
	fprintf(stderr,"Blue mask        = 0x%08lx\n", windowAttributes.visual->blue_mask);
	fprintf(stderr,"Bits per R/G/B   = %i\n", windowAttributes.visual->bits_per_rgb);
*/
	return w;
}
