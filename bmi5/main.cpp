#include <stdio.h>
#include "tdt_udp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <string.h>
#include <stack>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include "matio.h"

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

// C++11? 
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

// myopen common
#include "mmaphelp.h"
#include "gettime.h"
#include "timesync.h"
#include "perftimer.h"

//local.
#include "serialize.h"
#include "shape.h"
#include "polhemus.h"

using namespace std;
double	g_luaTime[4] = {0.0, 0.0, 0.0, 0.0}; //n, total time, max time, last time
double 	g_frameRate = 0.0; 
long double		g_lastFrame = 0.0; 
int		g_frame = 0;
bool 		g_glInitialized = false;
bool		g_glvsync = false; 
float		g_mousePos[2]; 
bool		g_die = false; 
bool		g_polhemusConnected = false; 
GtkWindow* g_mainWindow; //used for dialogs, etc. 
gtkglx*  g_daglx[2]; //human, monkey.
GtkWidget* g_da[2]; //draw areas. 
GtkWidget* g_luaTimeLabel; 
GtkWidget* g_openglTimeLabel; 
TimeSyncClient * g_tsc; 
unsigned char			g_writeBuffer[1024*1024]; 
PerfTimer	g_matlabTimer; 
PerfTimer	g_openGLTimer; 

// matlab-interactive objects. 
TimeSerialize* g_timeSerialize; 
Shape*		g_cursor; 
StarField* 	g_stars; 
PolhemusSerialize* g_polhemus; 
vector<Serialize*> g_objs; //container for each of these.

void UDP_RZ2(){
	int sock; 
 	sock = openSocket((char*)"169.230.191.195", LISTEN_PORT); 
	//sock = setup_socket(LISTEN_PORT); // joey's RZ2. 
	checkRZ(sock); 
	unsigned char buf[1024]; 
	double mean = 0; 
	double var = 0; 
	int np = 1; 
	double last = 0; 
	unsigned int oldpak = 0; 
	unsigned int dropped = 0; 
	while(1){
		//currently the socket is blocking -- will wait for data.
		unsigned int n = recv(sock, buf, 1024, 0);
		if(n > 0 && n < 1024){
			long double now = gettime(); 
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
int hostname_to_ip(char * hostname , char* ip){
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	if ( (he = gethostbyname( hostname ) ) == NULL){
		// get the host info
		herror("gethostbyname");
		return 1;
	}
	addr_list = (struct in_addr **) he->h_addr_list;
	for(i = 0; addr_list[i] != NULL; i++){
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return 0;
	}
	return 1;
}
void* syncThread(void*){
	int sock; 
	//need to do host resolution here ..
	char ipaddr[256]; 
	if(hostname_to_ip("GEDDA.local", ipaddr)){
		printf("could not resolve GEDDA.local\n"); 
 		return 0; 
	}
 	sock = openSocket(ipaddr, 27707); 
	// set a timeout of 1 sec..
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,  sizeof tv)){
		perror("setsockopt");
		return NULL;
	}
	unsigned char buf[1024]; 
	long double skew = 0.0; 
	long double delay = 0.0; 
	long double gain = 0.001; 
	long double lastupdate, fabsupdate; 
	lastupdate = 0.0; fabsupdate = 0.0; 
	while(!g_die){
		//send the time, as a double.
		double time = (double)gettime(); 
		int n = send(sock, &time, 8, 0); 
		if(n != 8) printf("sent length %d\n", n); 
		//currently the socket is blocking -- will wait for data.
		n = recv(sock, buf, 1024, 0);
		long double recvtime = gettime(); 
		if(n != 32){
			if(n > 0){
				buf[n]= 0; 
				printf("unexpected reply: %s\n", buf); 
			}
		}else{
			double* recv = (double*)buf; 
			long double skew_delay = recvtime - recv[0]; 
			//windows will report a skew_delay as well -- add them
			long double ld = (recv[1] + skew_delay)/2.0; 
			long double ls = (recv[1] - skew_delay)/2.0; 
			long double update = ls - skew; 
			skew = skew + gain*update; 
			delay = 0.999*delay + 0.001*ld; //this is purely diagnostic.
			printf("skew:%Lf delay %Lf gain %Lf metric %Lf update %Lf\n", skew, delay, gain, 
					 lastupdate/fabsupdate, update); 
			double g_offset = recv[2]; 
			double g_slope = recv[3]; 
			//use this to estimate the TDT clock. 
			long double ticks = ((recvtime + skew)*1000.0*g_slope + g_offset); 
			printf("estimated TDT ticks: %Lf offset %f slope %f\n", ticks, g_offset, g_slope); 
			//update the gain.
			if(fabsupdate > 0.0){
				if(fabs(lastupdate)/fabsupdate > 0.2) gain += 2.1861058423e-5; 
				else gain -= 1.2745310745e-5; 
			}
			if(gain > 0.5674529345) gain = 0.5674529345; if(gain < 1e-6) gain = 1e-6; 
			lastupdate = 0.95 * lastupdate + 0.05 * update; 
			fabsupdate = 0.95 * fabsupdate + 0.05 * fabs(update); 
			usleep(1000); 
		}
	}
	return NULL; 
}

void errorDialog(char* msg){
	GtkWidget *dialog, *label, *content_area;
	dialog = gtk_dialog_new_with_buttons ("Error",
							g_mainWindow,
							GTK_DIALOG_DESTROY_WITH_PARENT,
							GTK_STOCK_OK,
							GTK_RESPONSE_NONE,
							NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	label = gtk_label_new (msg);
	/* Ensure that the dialog box is destroyed when the user responds. */
	g_signal_connect_swapped (dialog,
							"response",
							G_CALLBACK (gtk_widget_destroy),
							dialog);
	/* Add the label, and show everything we've added to the dialog. */
	gtk_container_add (GTK_CONTAINER (content_area), label);
	gtk_widget_show_all (dialog);
}
void destroy(GtkWidget *, gpointer){
	//more cleanup later.
	g_die = true;
	KillFont(); 
	gtk_main_quit();
}
void updateCursPos(float x, float y){
	//always relative to the human view.
	g_mousePos[0] = x/(g_daglx[0]->m_size[0]);
	g_mousePos[1] = y/(g_daglx[0]->m_size[1]);
	//convert to -1 to +1
	for(int i=0; i<2; i++){
		g_mousePos[i] -= 0.5f;
		g_mousePos[i] *= 2.f;
	}
	g_mousePos[1] *= -1; //zero at the top for gtk; bottom for opengl.
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
	//printf("cursor position: %f %f\n", x, y); 
	return TRUE;
}
typedef GLvoid  
(*glXSwapIntervalSGIFunc) (GLint);  
static gboolean
configure1 (GtkWidget *da, GdkEventConfigure *, gpointer p)
{
	int h = (int)((long long)p & 0xf);
	if(h<0 || h>1) g_assert_not_reached ();
	//init the openGL context. 
	if(!(g_daglx[h]->configure(da))){
		g_assert_not_reached ();
	}
	//sync? only want for one monitor.
	if(h == 1){
		glXSwapIntervalSGIFunc glXSwapIntervalSGI = 0;  
		glXSwapIntervalSGI = (glXSwapIntervalSGIFunc)  
			glXGetProcAddressARB((const GLubyte*)"glXSwapIntervalSGI");  
		if (glXSwapIntervalSGI)  
				glXSwapIntervalSGI (g_glvsync ? 1 : 0); 
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
	g_stars->makeStars(3000, g_daglx[1]->getAR()); 
	g_stars->makeShaders(h); 
	return TRUE;
}

static gboolean
draw1 (GtkWidget *da, cairo_t *, gpointer p){
	long double t = gettime(); 
	g_openGLTimer.enter(); 
	int h = (int)((long long)p & 0xf);
	if(h <0 || h>1) g_assert_not_reached ();
	if (!(g_daglx[h]->expose(da))){
		g_assert_not_reached ();
	}
	if(da == g_da[1]){ //monkey view
		double dt = t - g_lastFrame; 
		g_lastFrame = t; 
		g_frameRate = 0.9 * g_frameRate + 0.1 / dt; 
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0,0,0,1); 
	
	glShadeModel(GL_FLAT);
	
	//g_cursor->translate(x,y); 
	//g_stars->m_vel[0] = g_mousePos[0] / -3.f;
	//g_stars->m_vel[1] = g_mousePos[1] / -3.f; 
	g_stars->draw(h); 
	g_cursor->draw(); 
	g_daglx[h]->swap(); //always double buffered.
	if(da == g_da[1]){ //update here, after the swap, for the 'smoothest' motion (?)
		t = gettime(); 
		g_stars->move(g_daglx[1]->getAR(), t);
		//g_cursor->translate(sin(t),cos(t)); 
	}
	g_openGLTimer.exit(); 
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
	char str[256];
	size_t n = matlabFileSize(g_objs); 
	snprintf(str, 256, "time:%.1f ms (mean)\n%.1f ms (last)\nfile size:%.2f MB", 
				g_matlabTimer.meanTime()*1000.0,
				g_matlabTimer.lastTime()*1000.0, 
				(float)n/(1024.f*1024.f));
	gtk_label_set_text(GTK_LABEL(g_luaTimeLabel), str); 
	
 	snprintf(str, 256, "frame rate: %4.1f Hz\nOpenGL run %.1f ms (mean)\n%.1f ms (last)", 
				g_frameRate, 
				g_openGLTimer.meanTime()*1000.0, 
				g_openGLTimer.lastTime()*1000.0); 
	gtk_label_set_text(GTK_LABEL(g_openglTimeLabel), str); 
	return TRUE;
}
static void printMmapStructure(GtkWidget*, gpointer ){
	//print the relevant matlab mmap infos. 
	printf("m2 = memmapfile('/tmp/bmi5_control', 'Format', {...\n"); 
	for(unsigned int i=0; i<g_objs.size(); i++){
		g_objs[i]->printMmapInfo(); 
	}
	printf("\t});\n"); 
}
static void fullscreenCB(GtkWidget* w, gpointer p){
	GtkWindow* top = GTK_WINDOW(p); 
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)))
		gtk_window_fullscreen(top);
	else
		gtk_window_unfullscreen(top);
}
static void vsyncCB(GtkWidget* w, gpointer){
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)))
		g_glvsync = true; 
	else
		g_glvsync = false; 
}
void flush_pipe(int fid){
	fcntl(fid, F_SETFL, O_NONBLOCK);
	char* d = (char*)malloc(1024*8); 
	int r = read(fid, d, 1024*8); 
	printf("flushed %d bytes\n", r); 
	free(d); 
	int opts = fcntl(fid,F_GETFL);
	opts ^= O_NONBLOCK;
	fcntl(fid, F_SETFL, opts);
}
/* matlab interaction -- through shared memory. */
void* mmap_thread(void*){
	size_t length = mmapFileSize(g_objs); 
	mmapHelp mmh(length, "/tmp/bmi5_control"); 
	
	int pipe_out = open("bmi5_out", O_RDWR); 
	if(pipe_out <= 0){
		perror("could not open ./bmi5_out (make with mkfifo)\n"); 
		return NULL; 
	}
	int pipe_in = open("bmi5_in", O_RDWR); 
	if(pipe_in <= 0){
		perror("could not open ./bmi5_in (make with mkfifo)\n"); 
		return NULL; 
	}
	mmh.prinfo(); 

	char buf[32]; int bufn = 0; 
	flush_pipe(pipe_out); 
	while(!g_die){
		//printf("%d waiting for matlab...\n", frame); 
		int r = read(pipe_in, &(buf[bufn]), 5);
		if(r > 0) bufn += r; 
		buf[bufn] = 0; 
		//printf("%d read %d %s\n", frame, r, buf); 
		if(r >= 3){
			//react to changes requested. 
			g_matlabTimer.exit(); 
			void* b = mmh.m_addr; 
			for(unsigned int i=0; i<g_objs.size(); i++)
				b = g_objs[i]->mmapRead(b); 
			for(unsigned int i=0; i<g_objs.size(); i++)
				g_objs[i]->store(); 
			
			usleep(100); //let the kernel sync memory.
			g_matlabTimer.enter(); 
			write(pipe_out, "go\n", 3); 
			//printf("sent pipe_out 'go'\n"); 
			bufn = 0; 
		}else
			usleep(200000); //does not seem to limit the frame rate, just the startup sync.
		g_frame++; 
	}
	close (pipe_in);
	close (pipe_out); 
	return NULL; 
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
		g_polhemusConnected = false; 
		return NULL; 
	}else{
		printf("polhemus connected via rs232!\n"); 
 		g_polhemusConnected = true;
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
	double frames = 0; 
	//now put it in binary (faster than ascii!) mode:
	pol->Write("f1\r"); 
	usleep(5000);
	len = pol->Read(buf, BUF_SIZE); //throw away.
	usleep(5000);
	// we only care about x, y, z -- faster (lower latency) transmission.
	pol->Write("O*,2\r"); //this command turns off sending Euler angles. 
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
			} while((len>0));
			if(start > 0){
				//printf("%d bytes Read\n",start);
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
					g_cbRN + 20 <= g_cbPtr){
					g_cbRN++; 
				}
				//printf("polhemus lag: %d\n", g_cbPtr - g_cbRN); 
				//this will either leave us aligned at the start of a frame
				//or waiting for more data.
				//copy between the current /r/n. 
				while(g_circBuff[g_cbRN % 1024] == 'L' && 
					g_circBuff[(g_cbRN+1) % 1024] == 'Y' && 
					g_cbRN + 20 <= g_cbPtr){
					for(i=0; i<20 && (g_cbRN+i) < g_cbPtr; i++){
						buf[i] = g_circBuff[(g_cbRN+i) % 1024]; 
					}
					buf[i] = 0; 
					//this data is used, move the pointer forward one. 
					g_cbRN += 20;
					// check for proper format LY for Liberty;  PA for Patriot
					float* pData=(float*)(buf+8);			// header is first 8 bytes
					g_polhemus->store(pData); 
					// print data
					//printf("x= %.4f, y= %.4f, z= %.4f, az= %.4f, el= %.4f, roll= %.4f\n",
					//	pData[0],pData[1],pData[2],pData[3],pData[4],pData[5]);
					//printf("x= %.4f, y= %.4f, z= %.4f,\n",
					//			pData[0],pData[1],pData[2]);
					frames += 1; 
					//printf("frame rate: %f\n", frames / (gettime() - starttime)); 
					/*if(g_sensors[0][2] > 0.0){
						g_sensors[0][0] *= -1.f;
						g_sensors[0][1] *= -1.f;
						//g_sensors[0][2] *= -1.f; 
					}*/
				}
			}
		}
	}
	pol->Write((void*)("p"), 1); //stop continuous mode.
	usleep(500); 
	pol->Close(); 
	return NULL;
}

static void saveMatlabData(gpointer parent_window) {
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Save Data File",
						(GtkWindow*)parent_window,
						GTK_FILE_CHOOSER_ACTION_SAVE,
						GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
						NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(
				GTK_FILE_CHOOSER (dialog), TRUE);
	gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog),"data.mat");
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
		char *filename;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		writeMatlab(g_objs, filename); 
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}

void longDoubleTest(){
	printf("sizeof long double %ld\n", sizeof(long double)); 
	printf("sizeof double %ld\n", sizeof(double)); 
	
	long double ld = 0.0; 
	double d = 0.0; 
	for(unsigned int i=0; i<100000000; i++){ //one billion!
		ld += 0.001234567; 
 		d += 0.001234567;
	}
	long double ld2 = (long double)d; 
	ld2 -= ld; 
	printf("sum ld: %Lf, d: %f difference %Lf\n", ld, d, ld2); 
}

void lambdaTest() {
	char s[]="Hello World!";
	int Uppercase = 0; //modified by the lambda
	for_each(s, s+sizeof(s), [&Uppercase] (char c) {
		if (isupper(c))
		Uppercase++;
		});
	cout<< Uppercase<<" uppercase letters in: "<< s<<endl;
}

int main(int argn, char** argc){
	//setup a window with openGL. 
	GtkWidget *window;
	GtkWidget *da1, *da2, *paned, *v1, *frame;
	
	g_startTime = gettime(); 
	
	gtk_init (&argn, &argc);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "sabes experimental control");
	gtk_window_set_default_size (GTK_WINDOW (window), 850, 650);

	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add (GTK_CONTAINER (window), paned);

	//left: gui etc. 
	v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(GTK_WIDGET(v1), 170, 650);
	
	frame = gtk_frame_new("Running stats");
	gtk_container_set_border_width (GTK_CONTAINER (frame), 5);
	gtk_box_pack_start (GTK_BOX (v1), frame, TRUE, TRUE, 0);
	g_luaTimeLabel = gtk_label_new("mean: max: %:"); 
	//gtk_misc_set_alignment (GTK_MISC (g_luaTimeLabel), 0, 0);
	gtk_container_add (GTK_CONTAINER (frame), g_luaTimeLabel );
	
	frame = gtk_frame_new("OpenGL stats");
	gtk_container_set_border_width (GTK_CONTAINER (frame), 5);
	gtk_box_pack_start (GTK_BOX (v1), frame, TRUE, TRUE, 0);
	g_openglTimeLabel = gtk_label_new("mean: max: %:"); 
	//gtk_misc_set_alignment (GTK_MISC (g_openglTimeLabel), 0, 0);
	gtk_container_add (GTK_CONTAINER (frame), g_openglTimeLabel );
	
	GtkWidget* button = gtk_button_new_with_label ("Save data");
	g_signal_connect(button, "clicked", G_CALLBACK(saveMatlabData), 0); 
	gtk_box_pack_start(GTK_BOX(v1), button, TRUE, TRUE, 0); 
	
	button = gtk_button_new_with_label ("print mmap structure");
	g_signal_connect(button, "clicked", G_CALLBACK(printMmapStructure), 0); 
	gtk_box_pack_start(GTK_BOX(v1), button, TRUE, TRUE, 0); 
	
	button = gtk_button_new_with_label ("stop");
	//g_signal_connect(button, "clicked", G_CALLBACK(luaStopCB), 0); 
	gtk_box_pack_start(GTK_BOX(v1), button, TRUE, TRUE, 0); 
	
	
	gtk_paned_add1(GTK_PANED(paned), v1);
	da1 = gtk_drawing_area_new ();
	gtk_paned_add2(GTK_PANED(paned), da1);
	
	//setup the opengl context for da1.
	//before we do this, tun on FSAA. 
	putenv( "__GL_FSAA_MODE=10" ); //http://www.opengl.org/discussion_boards/showthread.php/172000-Programmatically-controlling-level-of-AA
	putenv("__GL_SYNC_TO_VBLANK=0"); //don't sync to vertical blanking.  individually per window.
	putenv("__GL_SYNC_DISPLAY_DEVICE=DFP-3"); //sync to this display device. 
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
	
	auto makeCheckbox = [&](const char* lbl, bool ic, GCallback cb){
		button = gtk_check_button_new_with_label(lbl);
		gtk_box_pack_start (GTK_BOX (v1), button, TRUE, TRUE, 0);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (button), ic ? TRUE:FALSE); 
		gtk_widget_show (button);
		g_signal_connect (button, "clicked", cb, (gpointer*)top); 
	}; 
	
	//add a fullscreen checkbox to the gui.
	makeCheckbox("Fullscreen", false, G_CALLBACK(fullscreenCB)); 
	makeCheckbox("sync to Vblank", g_glvsync, G_CALLBACK(vsyncCB));  
	
	//can init the shapes ... here i guess (no opengl though!)
	g_timeSerialize = new TimeSerialize(); 
	g_cursor = new Shape(); 
	g_stars = new StarField(); 
	g_polhemus = new PolhemusSerialize(); 
	g_objs.push_back(g_timeSerialize); 
	g_objs.push_back(g_cursor); 
	g_objs.push_back(g_stars);
	g_objs.push_back(g_polhemus); 

	g_signal_connect_swapped (window, "destroy",
			G_CALLBACK (destroy), NULL);

	gtk_widget_show (window);
	gtk_widget_show (top);
	
	//add a refresh timeout. 
	g_da[0] = da1; 
	g_da[1] = da2; 
	g_timeout_add (4, refresh, da1); //250 Hz, approximate. 
	
	pthread_t pthread; 
	pthread_create(&pthread, NULL, polhemusThread, NULL); 
	pthread_t syncthread; 
	pthread_create(&syncthread, NULL, mmap_thread, NULL); 
	
	g_tsc = new TimeSyncClient(); //tells us the ticks when things happen.
	
	g_mainWindow = (GtkWindow*)window; 
	gtk_widget_show_all (window);
	gtk_main ();
	
	pthread_join(pthread,NULL);  // wait for the read thread to complete
	
	//save data!!
	writeMatlab(g_objs, "backup.mat"); 

	delete g_daglx[0];
	delete g_daglx[1]; 
	delete g_tsc; 
	for(unsigned int i=0; i<g_objs.size(); i++){
		delete (g_objs[i]); 
	}
	return 0; 
}
