#include <string.h>
#include <math.h>

//opengl headers.
#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include "glInfo.h"
#include "glFont.h"

GLuint 		g_base[2];            // base display list for the font set.

void BuildFont(int display)
{
	display &= 1;
	Display *dpy;
	XFontStruct *fontInfo;  // storage for our font.

	g_base[display] = glGenLists(96);                      // storage for 96 characters.

	// load the font.  what fonts any of you have is going
	// to be system dependent, but on my system they are
	// in /usr/X11R6/lib/X11/fonts/*, with fonts.alias and
	// fonts.dir explaining what fonts the .pcf.gz files
	// are.  in any case, one of these 2 fonts should be
	// on your system...or you won't see any text.

	// get the current display.  This opens a second
	// connection to the display in the DISPLAY environment
	// value, and will be around only long enough to load
	// the font.
	dpy = XOpenDisplay(NULL); // default to DISPLAY env.
	fontInfo = XLoadQueryFont(dpy, "-adobe-helvetica-medium-r-normal--16-*-*-*-p-*-iso8859-1");
	if (fontInfo == NULL) {
		fontInfo = XLoadQueryFont(dpy, "fixed");
		if (fontInfo == NULL) {
			printf("no X font available?\n");
		}
	}
	// after loading this font info, this would probably be the time
	// to rotate, scale, or otherwise twink your fonts.

	// start at character 32 (space), get 96 characters (a few characters past z), and
	// store them starting at base.
	glXUseXFont(fontInfo->fid, 32, 96, g_base[display]);

	// free that font's info now that we've got the
	// display lists.
	XFreeFont(dpy, fontInfo);

	// close down the 2nd display connection.
	XCloseDisplay(dpy);
}
void KillFont(int display)
{
	//printf("KillFont, %d\n", display);
	display &= 1;
	if (g_base[display]) {
		glDeleteLists(g_base[display], 96);                    // delete all 96 characters.
		g_base[display] = 0;
	}
}
void glPrint(const char *text, int display)
{
	display &= 1;
	if (text == NULL) {                         // if there's no text, do nothing.
		return;
	}
	glPushAttrib(GL_LIST_BIT);                  // alert that we're about to offset the display lists with glListBase
	glListBase(g_base[display] - 32);                      // sets the base character to 32.

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // draws the display list text.
	glPopAttrib();                              // undoes the glPushAttrib(GL_LIST_BIT);
}
