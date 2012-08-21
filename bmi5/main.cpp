#include <stdio.h>
#include "tdt_udp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

//lua headers.
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

//opengl headers. 
#include <gtk/gtk.h>
#include <GL/glut.h>    
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glx.h>    
#include "glext.h"
#include "glInfo.h"
#include "glFont.h"
#include "gtkglx.h"

#define PI 3.141592653589793

double 	g_startTime = 0.0;
bool		g_die = false; 
lua_State* g_lt; 

int main_sv(int argc, char **argv);

double gettime(){ //in seconds!
	timespec pt ;
	clock_gettime(CLOCK_MONOTONIC, &pt);
	double ret = (double)(pt.tv_sec) ;
	ret += (double)(pt.tv_nsec) / 1e9 ;
	return ret - g_startTime;
	//printf( "present time: %d s %d ns \n", pt.tv_sec, pt.tv_nsec ) ;
}

void UDP_RZ2(){
	int sock; 
 	sock = openSocket((char*)"169.230.191.195"); 
	//sock = setup_socket(LISTEN_PORT); // joey's RZ2. 
	checkRZ(sock); 
	unsigned char buf[1024]; 
	double mean = 0; 
	double var = 0; 
	int np = 1; 
	g_startTime = gettime(); 
	double last = 0; 
	unsigned int oldpak = 0; 
	unsigned int dropped = 0; 
	while(1){
		//currently the socket is blocking -- will wait for data.
		unsigned int n = recv(sock, buf, 1024, 0);
		if(n > 0 && n < 1024){
			double now = gettime(); 
 			np++; 
			double d = now - last; 
			mean += d; 
			double m = (mean / (double)np); 
			var += (d - m)*(d - m);
			//look for lost packets. 
			unsigned int paknum = htonl(*(unsigned int*)(&(buf[4])));  
			if(paknum - oldpak > 1 && paknum - oldpak < 20) 
				dropped += paknum - oldpak; 
			oldpak = paknum;
			printf("%x bytes: ", n); 
			for(unsigned int i=0; i<n; i++){
				printf("%02x ", buf[i]); 
			}
			printf("\n"); 
			printf("mean interpacket time %f std %f dropped %d\n", 
					 m, sqrt(var / (double)np), dropped); 
			last = now; 
		}
	}
}

bool 			g_glInitialized = false;
float			g_viewportSize[2] = {640, 480}; //width, height.
float			g_cursPos[2]; 

void luaRun(double &x, double &y){
	lua_getglobal(g_lt, "move"); 
	if(g_die) printf("telling lua thread to quit..\n"); 
	lua_pushnumber(g_lt, g_die ? 0.0 : 1.0); //tell the other thread to terminate.
	lua_pushnumber(g_lt, g_cursPos[0]); //number = double in this case.
	lua_pushnumber(g_lt, g_cursPos[1]); 
	int r = lua_resume(g_lt,3); //call 'move' with 2 arguments. kinda bad this is in the same thread..
	if(r == LUA_YIELD){
		x = lua_tonumber(g_lt, -1); 
		y = lua_tonumber(g_lt, -2); 
		//printf("lua results: %f %f\n", x, y); 
		lua_pop(g_lt, 2); //pop the results off the stack.
	}else if(r == LUA_ERRRUN){
		printf("%s\n", lua_tostring(g_lt, -1)); //print errors.
	}else{
		printf("lua function returned, not yielded.\n"); 
	}
}

void destroy(GtkWidget *, gpointer){
	//more cleanup later.
	g_die = true;
	KillFont(); 
	double x,y;
	luaRun(x,y); 
	lua_close(g_lt); 
	gtk_main_quit();
}

void updateCursPos(float x, float y){
	g_cursPos[0] = x/g_viewportSize[0];
	g_cursPos[1] = y/g_viewportSize[1];
	//convert to -1 to +1
	for(int i=0; i<2; i++){
		g_cursPos[i] -= 0.5f;
		g_cursPos[i] *= 2.f;
	}
	g_cursPos[1] *= -1; //zero at the top for gtk; bottom for opengl.
}

static gint motion_notify_event( GtkWidget *w,
                                 GdkEventMotion *){
	float x, y;
	int ix, iy;
	GdkDeviceManager *device_manager;
	GdkDevice *pointer;
	
	device_manager = gdk_display_get_device_manager (gtk_widget_get_display (w));
	pointer = gdk_device_manager_get_client_pointer (device_manager);
	gdk_window_get_device_position (gtk_widget_get_window (w), pointer, &ix, &iy, NULL);
	x = ix; y = iy;
	updateCursPos(x,y); 
	printf("cursor position: %f %f\n", x, y); 
	return TRUE;
}

static gboolean
configure1 (GtkWidget *da, GdkEventConfigure *, gpointer)
{
	//init the openGL context. 
	if(!configureGLX(da)){
		g_assert_not_reached ();
	}
	//save the viewport size.
	GtkAllocation allocation;
	gtk_widget_get_allocation (da, &allocation);
	g_viewportSize[0] = allocation.width;
	g_viewportSize[1] = allocation.height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (-1,1,-1,1,0,1);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
	if(!g_glInitialized){
	//now the vertex buffers.
		glInfo glInfo;
		glInfo.getInfo();
		printf("OpenGL version: %s\n", glInfo.version.c_str()); 
		//glInfo.printSelf();
		if(glInfo.isExtensionSupported("GL_ARB_vertex_buffer_object")){
			printf("Video card supports GL_ARB_vertex_buffer_object.\n");
		}else{
			printf("Video card does NOT support GL_ARB_vertex_buffer_object.\n");
		}
		g_glInitialized = true;
	}
	BuildFont(); //so we're in the right context?

	return TRUE;
}

void drawCircle(float x, float y, float r){
	int n = 32; 
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x,y); 
	for(int i=0; i<n; i++){
		float t = (float)i * PI * 2 / (n-1); 
		glVertex2f(x+r*sinf(t), y+r*cosf(t)); 
	}
	glEnd(); 
}

static gboolean
expose1 (GtkWidget *da, GdkEventExpose* event, gpointer )
{
	if (event->count > 0) return TRUE;
	
	if (!exposeGLX(da)){
		g_assert_not_reached ();
	}
	
	/* draw in here */
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glColor4f(1.f, 1.f, 1.f, 0.75);
	
	// run some lua here. 
	double x = 0.0; 
	double y = 0.0; 
	luaRun(x,y); 
	drawCircle(x, y, 0.5f); 
	
	swapGLX(); //always double buffered.

	return TRUE;
}

static gboolean refresh (gpointer user_data){
	GtkWidget *da = GTK_WIDGET (user_data);
	gtk_widget_queue_draw (da);

	//can do other pre-frame GUI update stuff here.
	return TRUE;
}

static void notebookPageChangedCB(GtkWidget *,
					gpointer, int page, gpointer){
	printf("tab %d selected!\n", page); 
}

int main(int argn, char** argc){
	//setup a window with openGL. 
	GtkWidget *window;
	GtkWidget *da1, *da2, *notebook, *paned, *v1, *label;

	/* Declare a Lua State, open the Lua State and load the libraries (see above). */
	lua_State *l;
	l = luaL_newstate(); 
	luaopen_base(l);
	luaopen_table(l); 
	luaopen_math(l); 
	luaopen_debug(l); 

	// want to make a Lua function that yeilds() 
	// instead of a big ugly switch statement. 
	//first make a thread and push it on the stack.
	g_lt = lua_newthread(l); 
	printf("This line in directly from C\n\n");
	if(luaL_dofile(g_lt, "script.lua")) //inits the function.
		printf("%s\n", lua_tostring(g_lt, -1)); //print errors.
	double x, y; 
	luaRun(x,y); 
	
	gtk_init (&argn, &argc);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "sabes experimental control");
	gtk_window_set_default_size (GTK_WINDOW (window), 850, 650);

	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add (GTK_CONTAINER (window), paned);

	//left: gui etc. 
	v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(GTK_WIDGET(v1), 200, 600);
	
	//right: tabbed ('notebook') graphics windows. 
	notebook = gtk_notebook_new(); 
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
	g_signal_connect(notebook, "switch-page",
					 G_CALLBACK(notebookPageChangedCB), 0);
	gtk_widget_set_size_request(GTK_WIDGET(notebook), 640, 650);
	
	gtk_paned_add1(GTK_PANED(paned), v1);
	gtk_paned_add2(GTK_PANED(paned), notebook);
	
	da1 = gtk_drawing_area_new ();
	label = gtk_label_new("tab1");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), da1, label, 0);
	
	da2 = gtk_drawing_area_new ();
	label = gtk_label_new("tab2");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), da2, label, 1);
	
	//setup the opengl context for da1.
	gtk_widget_set_double_buffered (da1, FALSE);
	setupGLX(da1); 
	g_signal_connect (da1, "configure-event",
			G_CALLBACK (configure1), NULL);
	g_signal_connect (da1, "expose-event",
			G_CALLBACK (expose1), NULL);
	g_signal_connect (da1, "realize", G_CALLBACK (realizeGLX), window);
	g_signal_connect (da1, "motion_notify_event",
			G_CALLBACK (motion_notify_event), NULL);
	gtk_widget_set_events(da1, GDK_EXPOSURE_MASK);
	//in order to receive keypresses, must be focusable!
	gtk_widget_set_can_focus(da1, TRUE);
	/*
	gtk_widget_set_events (da, GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); */
	
	//also add a SourceView widget (?)
	GtkWidget* scrolled = gtk_scrolled_window_new(NULL,NULL); 
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled),
                                    GTK_POLICY_AUTOMATIC, 
                                    GTK_POLICY_AUTOMATIC);
	label = gtk_label_new("source");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), scrolled, label, 2);

	gtk_widget_show (paned);
	gtk_widget_show (notebook);

	g_signal_connect_swapped (window, "destroy",
			G_CALLBACK (destroy), NULL);

	gtk_widget_show (window);
	
	//add a refresh timeout. 
	g_timeout_add (1000 / 60, refresh, da1);
	
	//editor?
 	//main_sv(argn, argc); 
	
	gtk_widget_show_all (window);
	gtk_main ();
	
	//lua_close(l);
	return 0; 
}

