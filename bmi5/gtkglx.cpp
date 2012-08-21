/** GLX **/
// gtkglext is not compatible with gtk-3.0
// but, we can manage our own GLX calls.

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <GL/glut.h>    
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glx.h>  


typedef struct {
	/*GdkColormap 	*colormap;*/
	Colormap 		xcolormap;
	GdkVisual* 		visual;
	XVisualInfo 	*xvisual;
	Display 			*display;
	GLXContext 		context;
	int				xid;
} gtkglx; 

gtkglx* g; 

void setupGLX(GtkWidget *){
	GdkScreen 		*screen;
	int 				xscreen;
	Window 			root;
	
	int attributes[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1, GLX_DOUBLEBUFFER, True, GLX_DEPTH_SIZE, 12, None };

	g = (gtkglx*)malloc(sizeof(gtkglx)); 
	
	g->display = gdk_x11_get_default_xdisplay ();
	xscreen = DefaultScreen (g->display);
	screen = gdk_screen_get_default ();
	g->xvisual = glXChooseVisual (g->display, xscreen, attributes);
	g->visual = gdk_x11_screen_lookup_visual (screen, g->xvisual->visualid);
	root = RootWindow (g->display, xscreen);
	g->xcolormap = XCreateColormap(g->display, root, 
											 g->xvisual->visual, AllocNone);
	/*g->colormap = gdk_x11_colormap_foreign_new (g->visual, g->xcolormap); 
	gtk_widget_set_colormap (area, g->colormap);*/
	g->context = glXCreateContext (g->display, g->xvisual, NULL, TRUE);

}

void freeGLX(){
	glXDestroyContext (g->display, g->context);
	XFreeColormap (g->display, g->xcolormap);
	XFree (g->xvisual);
	//g_object_unref (G_OBJECT (g->colormap));
	g_object_unref (G_OBJECT(g->visual));
	free(g); 
}

int configureGLX(GtkWidget *widget){
	GtkAllocation allocation;
	GdkWindow *window;
	Display *display;
	int id;

	window = gtk_widget_get_window (widget);
	display = GDK_WINDOW_XDISPLAY(window);
	id = gdk_x11_window_get_xid (window);

	if (glXMakeCurrent (display, id, g->context) == TRUE){
		gtk_widget_get_allocation (widget, &allocation);
		glViewport (0, 0, allocation.width, allocation.height);
		return 1; 
	}
	return 0; 
}

int realizeGLX(GtkWidget *w, void*){ //extra parameter so it can be a cb.
	GdkWindow *window;
	Display *display;
	int id;

	window = gtk_widget_get_window (w);
	display = GDK_WINDOW_XDISPLAY(window);
	id = gdk_x11_window_get_xid (window);

	if (glXMakeCurrent (display, id, g->context) == TRUE){
		glEnable (GL_DEPTH_TEST);
		glDepthFunc (GL_LEQUAL);
		glEnable (GL_CULL_FACE);
		glCullFace (GL_BACK);
		glDisable (GL_DITHER);
		glShadeModel (GL_SMOOTH);
	}

	return TRUE;
}

int exposeGLX(GtkWidget *widget){
	GdkWindow *window;
	Display *display;

	window = gtk_widget_get_window (widget);
	display = GDK_WINDOW_XDISPLAY(window);
	g->xid = gdk_x11_window_get_xid (window);

	if (glXMakeCurrent (display, g->xid, g->context) == TRUE)
		return 1; //success!
	return 0; 
}

void swapGLX(){
	glXSwapBuffers (g->display, g->xid);
}