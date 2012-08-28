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
/*#include <luajit-2.0/lua.h>
#include <luajit-2.0/lauxlib.h>
#include <luajit-2.0/lualib.h> -- these don't work, ??? */

//opengl headers. 
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <GL/glew.h>
#include <GL/glut.h>    
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glx.h> 
#include <GL/glext.h> 
#include "glInfo.h"
#include "glFont.h"
#include "gtkglx.h"
#include "shape.h"
#include "polhemus.h"

//srcview headers. 
#include <gtksourceview/gtksourceview.h>
#include "srcView.h"

double 	g_startTime = 0.0;
bool		g_die = false; 
lua_State* g_lt; 
Shape*	g_cursor; 
StarField* g_stars; 
gtkglx*  g_daglx[2]; //human, monkey.
GtkWidget* g_da[2]; 

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
	//always relative to the human view.
	g_cursPos[0] = x/(g_daglx[0]->m_size[0]);
	g_cursPos[1] = y/(g_daglx[0]->m_size[1]);
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
configure1 (GtkWidget *da, GdkEventConfigure *, gpointer p)
{
	int h = (int)((long long)p & 0xf);
	if(h<0 || h>1) g_assert_not_reached ();
	//init the openGL context. 
	if(!(g_daglx[h]->configure(da))){
		g_assert_not_reached ();
	}
	//save the viewport size.
	GtkAllocation allocation;
	gtk_widget_get_allocation (da, &allocation);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//normalize vertical axis. 
	float ar = g_daglx[h]->m_size[0] / g_daglx[h]->m_size[1]; 
	glOrtho (-1.f*ar,ar,-1,1,0,1);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
	if(!g_glInitialized){
	//now the vertex buffers.
		glewExperimental = GL_TRUE;  //needed for glGenVertexArrays.
		GLenum err = glewInit();
		if(err != GLEW_OK){
			/* Problem: glewInit failed, something is seriously wrong. */
			printf("Error: %s\n", glewGetErrorString(err));
		}
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
	BuildFont(); //so we're in the right context.
	//have to create the shapes here -- context again.
	g_cursor->makeCircle(64); 
	g_cursor->scale(0.5); 
	g_stars->makeStars(1000, g_daglx[1]->getAR()); 

	return TRUE;
}

static gboolean
draw1 (GtkWidget *da, cairo_t *, gpointer p){
	int h = (int)((long long)p & 0xf);
	if(h <0 || h>1) g_assert_not_reached ();
	if (!(g_daglx[h]->expose(da))){
		g_assert_not_reached ();
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0,0,0,1); 
	
	glShadeModel(GL_FLAT);
	glColor4f(0.7f, 1.f, 1.f, 0.75);
	
	// run some lua here. 
	double x = 0.0; 
	double y = 0.0; 
	luaRun(x,y); 
	g_cursor->translate(x,y); 
	g_cursor->draw(); 
	g_stars->m_vel[0] = g_cursPos[0] / -3.f;
	g_stars->m_vel[1] = g_cursPos[1] / -3.f; 
	g_stars->move(0.01, g_daglx[1]->getAR()); //really should have the actual time here.
	g_stars->draw(); 
	
	g_daglx[h]->swap(); //always double buffered.

	return TRUE;
}

static int realize1(GtkWidget *w, gpointer p){
	int h = (int)((long long)p & 0xf);
	if(h <0 || h>1) g_assert_not_reached ();
	if(!(g_daglx[h]->realize(w))){
		g_assert_not_reached ();
	}
	return TRUE;
}

static gboolean refresh (gpointer ){
	//GtkWidget **da = GTK_WIDGET (user_data);
	gtk_widget_queue_draw (g_da[0]);
	gtk_widget_queue_draw (g_da[1]);
	//can do other pre-frame GUI update stuff here.
	return TRUE;
}

static void notebookPageChangedCB(GtkWidget *,
					gpointer, int page, gpointer){
	printf("tab %d selected!\n", page); 
}

/* Liberty / Polhemus. 
 as reading from USB / serial will take some time, it makes sense to 
 put this in a separate thread, with mutex so that the instant the data is 
 available, we pass it through the task logic & display on screen
 (or control microstimulation). 
 There seems no lower latency way ... 
 While writing floats is likely atomic, writing three floats is not -- 
 hence the need for interlock. 
 */
#define BUF_SIZE 1000
float g_sensors[2][6]; 
char g_circBuff[1024]; 
unsigned int g_cbPtr = 0; 
unsigned int g_cbRN = 0; //pointer to the last carrige return.

void* polhemusThread(void* ){
	
	unsigned char buf[BUF_SIZE];
	int count, start, len, i;
	
	//init the communication obj.
	polhemus* pol = new polhemus(); 
	if(!pol){
		printf("Memory Allocation Error creating tracker object\n");
		return NULL;
	}
	int fail; 
	//fail = pol->UsbConnect(TRKR_LIB); //see polhemus.h
	fail = pol->Rs232Connect("/dev/ttyS2", 115200); 
	if(fail){
		printf("could not establish a rs232 connection to the Polhemus / liberty\n");
	}else{
		printf("polhemus connected via rs232!\n"); 
	}
	//flush the buffer, sync things up.
	count = 0; 
	do {
		if(count <20)
			pol->Write("p"); //request position data (and stop continuous..)
		usleep(5000); 
		len=pol->Read(buf,BUF_SIZE);  // keep trying till we get a response
		count++; 
	} while (len > 0);
	// first establish comm and clear out any residual trash data
	double starttime = gettime(); 
	double frames = 0; 
	//now put it in binary (faster than ascii!) mode:
	pol->Write("f1\r"); 
	usleep(5000);
	len = pol->Read(buf, BUF_SIZE); //throw away.
	usleep(5000);
	// we only care about x, y, z -- faster (lower latency) transmission.
	pol->Write("O*,2\r"); //this command turns off sending euler angles. 
	pol->Write("c\r"); //request continuous data.
	// and read the data in a loop.
	g_cbPtr = g_cbRN = 0; 
	while(!g_die){
		if(1){ //binary communication. slow?
			//pol->Write((void*)("p"), 1); //request position data.
			start = count = 0;
			memset(buf, 0, 40); 
			usleep(200);
			do {
				len = pol->Read(buf+start, BUF_SIZE-start); 
				if(len>0) start+=len;
				usleep(100);
			} while((len>0) || (count++ < 5));
			if(start > 0){
				printf("%d bytes Read\n",start);
				//frame starts with 'LY_P', and is 8 bytes. This is followed by 3 4-byte floats.
				//total frame is hence 20 bytes. 
				for(i=0; i<start; i++){
					g_circBuff[g_cbPtr % 1024] = buf[i]; 
					g_cbPtr++; 
				}
				// align to frame.
				while(((g_circBuff[g_cbRN % 1024] != 'L') || 
					(g_circBuff[(g_cbRN+1) % 1024] != 'Y') || 
					(g_circBuff[(g_cbRN+2) % 1024] != 0x01)) &&
					g_cbRN + 20 < g_cbPtr){
					g_cbRN++; 
				}
				//this will either leave us aligned at the start of a frame
				//or waiting for more data.
				//copy between the current /r/n. 
				if(g_circBuff[g_cbRN % 1024] == 'L' && g_circBuff[(g_cbRN+1) % 1024] == 'Y'){
					for(i=0; i<20 && (g_cbRN+i) < g_cbPtr; i++){
						buf[i] = g_circBuff[(g_cbRN+i) % 1024]; 
					}
					buf[i] = 0; 
					//this data is used, move the pointer forward one. 
					g_cbRN++;
					// check for proper format LY for Liberty;  PA for Patriot
					float* pData=(float*)(buf+8);			// header is first 8 bytes
					// print data
					//printf("x= %.4f, y= %.4f, z= %.4f, az= %.4f, el= %.4f, roll= %.4f\n",
					//	pData[0],pData[1],pData[2],pData[3],pData[4],pData[5]);
					printf("x= %.4f, y= %.4f, z= %.4f,\n",
								pData[0],pData[1],pData[2]);
					frames += 1; 
					printf("frame rate: %f\n", frames / (gettime() - starttime)); 
					for(i=0; i<3; i++){
						g_sensors[0][i] = pData[i]; 
					}
					if(g_sensors[0][2] > 0.0){
						g_sensors[0][0] *= -1.f;
						g_sensors[0][1] *= -1.f;
						g_sensors[0][2] *= -1.f; 
					}
				}
			}
		}
	}
	pol->Write((void*)("p"), 1); //stop continuous mode.
	usleep(500); 
	pol->Close(); 
	return NULL;
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
	label = gtk_label_new("task");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), da1, label, 0);
	
	//setup the opengl context for da1.
	gtk_widget_set_double_buffered (da1, FALSE);
	g_daglx[0] = new gtkglx(da1); 
 
	g_signal_connect (da1, "configure-event",
			G_CALLBACK (configure1), 0);
	g_signal_connect (da1, "draw",
			G_CALLBACK (draw1), 0);
	g_signal_connect (da1, "realize", 
			G_CALLBACK (realize1), 0);
	g_signal_connect (da1, "motion_notify_event",
			G_CALLBACK (motion_notify_event), NULL);
	//in order to receive keypresses, must be focusable!
	gtk_widget_set_can_focus(da1, TRUE);
	
	gtk_widget_set_events (da1, GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); 
	
	gtk_widget_show (da1);
	
	//make the aux / monkey window. 
	GtkWidget* top = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (top), "m0nkey view");
	gtk_window_set_default_size (GTK_WINDOW (top), 640, 480);
	da2 = gtk_drawing_area_new ();
	gtk_container_add (GTK_CONTAINER (top), da2);
	gtk_widget_set_double_buffered (da2, FALSE);
	g_daglx[1] = new gtkglx(da2); 
	
	g_signal_connect (da2, "configure-event",
			G_CALLBACK (configure1), (void*)1);
	g_signal_connect (da2, "draw",
			G_CALLBACK (draw1), (void*)1);
	g_signal_connect (da2, "realize", 
			G_CALLBACK (realize1), (void*)1);
	//in order to receive keypresses, must be focusable!
	//gtk_widget_set_can_focus(da2, TRUE);
	
	gtk_widget_set_events (da2, GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); 
	
	gtk_widget_show (da2);
	
	//can init the shapes ... here i guess (no opengl though!)
	g_cursor = new Shape(); 
	g_stars = new StarField(); 
	
	//also add a SourceView widget (?)
	GtkSourceBuffer *buffer = gtk_source_buffer_new (NULL);
	open_file (buffer, "script.lua");
	GtkWidget* srcview = create_main_window(window, buffer); 
	label = gtk_label_new("source");
	gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), srcview, label, 1);

	gtk_widget_show (paned);
	gtk_widget_show (notebook);

	g_signal_connect_swapped (window, "destroy",
			G_CALLBACK (destroy), NULL);

	gtk_widget_show (window);
	gtk_widget_show (top);
	
	//add a refresh timeout. 
	g_da[0] = da1; 
	g_da[1] = da2; 
	g_timeout_add (1000 / 120, refresh, da1); //120 Hz refresh. twice as fast as needed.
	
	pthread_t pthread; 
	pthread_create(&pthread, NULL, polhemusThread, NULL); 
	
	gtk_widget_show_all (window);
	gtk_main ();
	
	//lua_close(l);
	pthread_join(pthread,NULL);  // wait for the read thread to complete
	delete g_daglx[0];
	delete g_daglx[1]; 
	return 0; 
}

