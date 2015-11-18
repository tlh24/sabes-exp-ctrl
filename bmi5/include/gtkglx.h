#ifndef __GTKGLX_H__
#define __GTKGLX_H__

// gtkglext is not compatible with gtk-3.0
// but, we can manage our own GLX calls.

/* needed headers: (in this order)
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
*/
class gtkglx
{
	Colormap 		m_xcolormap;
	//GdkVisual 		*m_visual;
	XVisualInfo 	*m_xvisual;
	Display 		*m_display;
	GLXContext 		m_context;
	int				m_xid;
public:
	float				m_size[2];

	gtkglx(GtkWidget *)
	{
		//GdkScreen 		*screen;
		int 				xscreen;
		Window 			root;

		int attributes[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1,
		                     GLX_BLUE_SIZE, 1, GLX_DOUBLEBUFFER, False, GLX_DEPTH_SIZE, 12, None
		                   };

		m_display = gdk_x11_get_default_xdisplay ();
		xscreen = DefaultScreen (m_display);
		//screen = gdk_screen_get_default ();
		m_xvisual = glXChooseVisual (m_display, xscreen, attributes);
		//m_visual = gdk_x11_screen_lookup_visual (screen, m_xvisual->visualid);
		root = RootWindow (m_display, xscreen);
		m_xcolormap = XCreateColormap(m_display, root,
		                              m_xvisual->visual, AllocNone);
		m_context = glXCreateContext (m_display, m_xvisual, nullptr, TRUE);
		m_size[0] = m_size[1] = 1.f;
	}
	~gtkglx()
	{
		glXDestroyContext (m_display, m_context);
		XFreeColormap (m_display, m_xcolormap);
		//g_object_unref (G_OBJECT(m_visual));
		XFree (m_xvisual);
	}
	int configure(GtkWidget *widget)
	{
		GtkAllocation allocation;
		GdkWindow *window;
		Display *display;
		int id;

		window = gtk_widget_get_window (widget);
		display = GDK_WINDOW_XDISPLAY(window);
		id = gdk_x11_window_get_xid (window);

		if (glXMakeCurrent (display, id, m_context) == TRUE) {
			gtk_widget_get_allocation (widget, &allocation);
			glViewport (0, 0, allocation.width, allocation.height);
			m_size[0] = allocation.width;
			m_size[1] = allocation.height;
		}
		return TRUE;
	}
	int realize(GtkWidget *w)   //extra parameter so it can be a cb.
	{
		GdkWindow *window;
		Display *display;
		int id;

		window = gtk_widget_get_window(w);
		display = GDK_WINDOW_XDISPLAY(window);
		id = gdk_x11_window_get_xid (window);

		if (glXMakeCurrent (display, id, m_context) == TRUE) {
			glEnable (GL_DEPTH_TEST);
			glDepthFunc (GL_LEQUAL);
			glDisable (GL_CULL_FACE);
			//glCullFace (GL_BACK);
			glDisable (GL_DITHER);
			glShadeModel (GL_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			//glEnable(GL_POLYGON_SMOOTH); looks bad -- triangles don't mesh well.
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		}

		return TRUE;
	}
	int expose(GtkWidget *widget)
	{
		GdkWindow *window;
		Display *display;

		window = gtk_widget_get_window (widget);
		display = GDK_WINDOW_XDISPLAY(window);
		m_xid = gdk_x11_window_get_xid (window);

		if (glXMakeCurrent (display, m_xid, m_context) == TRUE)
			return TRUE; //success!
		return FALSE;
	}
	void swap()
	{
		glFlush();
		glXSwapBuffers (m_display, m_xid);
	}
	float getAR()
	{
		return m_size[0] / m_size[1];
	}
};
#endif
