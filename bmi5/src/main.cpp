#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <proc/readproc.h>
#include <math.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stack>
#include <string>
#include <iomanip>
#include <limits>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <fcntl.h>
#include <pcap.h>
#include "matio.h"

// XDG
#include <basedir.h>
#include <basedir_fs.h>

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

// C++11
#include <iostream>
#include <fstream>
#include <streambuf>
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
#include "fifohelp.h"

//local
#include "tdt_udp.h"
#include "jacksnd.h"
#include "serialize.h"
#include "shape.h"
#include "polhemus.h"
#include "glFont.h"

#include "fenv.h" // for debugging nan problems
#include "libgen.h"

#ifdef LABJACK
#include "u6.h"
#endif

#ifdef OPTO
#include "../optotrak_sniff/etherstruct.h"
#endif

// conf files
#include "lualib.h"
#include "lauxlib.h"
#include "lconf.h"

using namespace std;
using namespace boost;

string 		g_mmap = "/tmp/bmi5_control.mmap";
string 		g_in_fifo = "/tmp/bmi5_in.fifo";
string 		g_out_fifo = "/tmp/bmi5_out.fifo";
string 		g_polhemus_serial = "/dev/ttyS0";

bool 		g_do_backup = true;
string 		g_backup_dir = "/tmp";

double 		g_frameRate = 0.0;
long double	g_lastFrame = 0.0;
int			g_frame = 0;
int 		g_nCommand = 0; //number of matlab commands recieved.
bool 		g_glInitialized[2] = {false};
bool		g_glvsync = false;
bool		g_renderOpView = false;
float		g_mousePos[2];
bool		g_die = false;
bool		g_record = false;
bool		g_polhemusConnected = false;
bool		g_optoConnected = false;
bool		g_labjackConnected = false;
GtkWindow 	*g_mainWindow; //used for dialogs, etc.
gtkglx  	*g_daglx[2]; //monkey, human.
GtkWidget 	*g_da[2]; //draw areas, same order as above.
GtkWidget 	*g_timeLabel;
GtkWidget 	*g_matlabTimeLabel;
GtkWidget 	*g_openglTimeLabel;
GtkWidget 	*g_polhemusLabel;
GtkWidget 	*g_optoLabel;
string		g_optoLabelStr;
GtkWidget	*g_labjackLabel;
string		g_labjackLabelStr;
TimeSyncClient *g_tsc;
unsigned char g_writeBuffer[1024*1024];
PerfTimer	g_matlabTimer;
PerfTimer	g_openGLTimer;
VsyncTimer	g_vsyncTimer;

// matlab-interactive objects.
TimeSerialize 		*g_timeSerialize;
FrameSerialize 	*g_frameSerialize;
Matrix44Serialize	*g_affine44; //used for translating world->screen coordinates.
Matrix44Serialize	*g_quadratic44;
PolhemusSerialize 	*g_polhemus;
OptoSerialize 		*g_opto; //the optotrak.
MouseSerialize		*g_mouse; //mouse control.
LabjackSerializeAIN	*g_labjack_AIN; //USB analog input.
LabjackSerializeDOUT	 *g_labjack_DOUT; //USB digital output
vector<Serialize *> 	g_objs; //container for each of these, and more!

pthread_mutex_t		mutex_fwrite; //mutex on file-writing, between automatic backup & user-initiated.
pthread_mutex_t		mutex_gobjs;
long double			g_nextVsyncTime = -1;

luaConf 			g_lc;

string 				g_basedirname;

//forward decl.
void gobjsInit();

void errorDialog(char *msg)
{
	GtkWidget *dialog, *label, *content_area;
	dialog = gtk_dialog_new_with_buttons ("Error",
	                                      g_mainWindow,
	                                      GTK_DIALOG_DESTROY_WITH_PARENT,
	                                      "_OK",
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
void destroy(int)
{
	//more cleanup later.
	g_die = true;
	sleep(1);
	gtk_main_quit();
	KillFont(0);
	KillFont(1);
}
void destroyGUI(GtkWidget *, gpointer)
{
	destroy(SIGINT);
}
void updateCursPos(float x, float y)
{
	//always relative to the human view.
	g_mousePos[0] = x/(g_daglx[1]->m_size[0]);
	g_mousePos[1] = y/(g_daglx[1]->m_size[1]);
	//convert to -1 to +1
	for (int i=0; i<2; i++) {
		g_mousePos[i] -= 0.5f;
		g_mousePos[i] *= 2.f;
	}
	g_mousePos[1] *= -1; //zero at the top for gtk; bottom for opengl.
	//printf("cursor position: %f %f\n", g_mousePos[0], g_mousePos[1]);
}
static gint motion_notify_event( GtkWidget *w, GdkEventMotion *)
{
	float x, y;
	int ix, iy;
	GdkDeviceManager *device_manager;
	GdkDevice *pointer;

	device_manager = gdk_display_get_device_manager (gtk_widget_get_display (w));
	pointer = gdk_device_manager_get_client_pointer (device_manager);
	gdk_window_get_device_position (gtk_widget_get_window (w), pointer, &ix, &iy, NULL);
	x = ix;
	y = iy;
	updateCursPos(x,y);
	return TRUE;
}
typedef GLvoid
(*glXSwapIntervalSGIFunc) (GLint);
static gboolean
configure1 (GtkWidget *da, GdkEventConfigure *, gpointer p)
{
	int h = (int)((long long)p & 0xf);
	if (h<0 || h>1) g_assert_not_reached ();
	//init the openGL context.
	if (!(g_daglx[h]->configure(da))) {
		g_assert_not_reached ();
	}
	//sync? only want for one monitor.
	if (h == 0) {
		glXSwapIntervalSGIFunc glXSwapIntervalSGI = 0;
		glXSwapIntervalSGI = (glXSwapIntervalSGIFunc)
		                     glXGetProcAddressARB((const GLubyte *)"glXSwapIntervalSGI");
		if (glXSwapIntervalSGI)
			glXSwapIntervalSGI(g_glvsync ? 1 : 0);
		//font on this one too.
	}
	KillFont(h);
	BuildFont(h);

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
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (!g_glInitialized[h]) {
		//now the vertex buffers.
		glewExperimental = GL_TRUE;  //needed for glGenVertexArrays.
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			/* Problem: glewInit failed, something is seriously wrong. */
			printf("Error: %s\n", glewGetErrorString(err));
		}
		glInfo glInfo;
		glInfo.getInfo();
		printf("OpenGL version: %s\n", glInfo.version.c_str());
		//glInfo.printSelf();
		if (glInfo.isExtensionSupported("GL_ARB_vertex_buffer_object")) {
			printf("Video card supports GL_ARB_vertex_buffer_object.\n");
		} else {
			printf("Video card does NOT support GL_ARB_vertex_buffer_object.\n");
		}
		g_glInitialized[h] = true;
	}
	//have to create the shapes here -- context again.
	return TRUE;
}

static gboolean
draw1 (GtkWidget *da, cairo_t *, gpointer p)
{
	long double t = gettime();
	int h = (int)((long long)p & 0xf);
	if (h <0 || h>1) g_assert_not_reached ();
	if (!(g_daglx[h]->expose(da))) {
		g_assert_not_reached ();
	}
	if (da == g_da[0]) { //monkey view
		double dt = t - g_lastFrame;
		g_lastFrame = t;
		g_frameRate = 0.9 * g_frameRate + 0.1 / dt;
	}
	if (da == g_da[0] || g_renderOpView) {
		g_openGLTimer.enter();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0,0,0,1);
		glShadeModel(GL_FLAT);

		/// draw objects
		//update before the swap for minimum display latency.
		pthread_mutex_lock(&mutex_gobjs);
		float ar = 1.f;
		if (da == g_da[0]) {
			t = gettime();
			for (unsigned int i=0; i<g_objs.size(); i++)
				g_objs[i]->move(t);
		} else {
			//convert between aspect-ratios.
			ar = g_daglx[0]->getAR() / g_daglx[1]->getAR();
		}
		for (unsigned int i=0; i<g_objs.size(); i++)
			g_objs[i]->draw(h, ar);
		pthread_mutex_unlock(&mutex_gobjs);
		/// end

		g_daglx[h]->swap(); //always double buffered
		g_openGLTimer.exit();
	}
	if (da == g_da[0]) {
		if (g_record) g_frameSerialize->store(g_frame);
		g_frame++;
		g_nextVsyncTime = g_vsyncTimer.add(gettime());
	}
	return TRUE;
}

static int realize1(GtkWidget *w, gpointer p)
{
	int h = (int)((long long)p & 0xf);
	if (h <0 || h>1) g_assert_not_reached ();
	if (!(g_daglx[h]->realize(w))) {
		g_assert_not_reached ();
	}
	return TRUE;
}

static gboolean refresh (gpointer )
{
	if (g_die)
		return false;

	//GtkWidget **da = GTK_WIDGET (user_data);
	gtk_widget_queue_draw (g_da[0]);
	gtk_widget_queue_draw (g_da[1]);
	//can do other pre-frame GUI update stuff here.
	long double time;
	double ticks;
	g_tsc->getTicks(time, ticks); //force mmap update.
	string s = g_tsc->getInfo();
	gtk_label_set_text(GTK_LABEL(g_timeLabel), s.c_str());
	char str[256];
	size_t n = 0;
	if (pthread_mutex_trylock(&mutex_gobjs) == 0) {
		n = matlabFileSize(g_objs); //no problem if it's locked elsewhere; this is just GUI.
		pthread_mutex_unlock(&mutex_gobjs);
	}
	snprintf(str, 256, "time:\t%.1f ms (mean)\n\t\t%.1f ms (last)\nfile size:\t%.2f MB",
	         g_matlabTimer.meanTime()*1000.0,
	         g_matlabTimer.lastTime()*1000.0,
	         (float)n/(1024.f*1024.f));
	gtk_label_set_text(GTK_LABEL(g_matlabTimeLabel), str);

	snprintf(str, 256, "fps:\t\t%4.1f Hz\ntime:\t%.1f ms (mean)\n\t\t%.1f ms (last)",
	         g_frameRate,
	         g_openGLTimer.meanTime()*1000.0,
	         g_openGLTimer.lastTime()*1000.0);
	gtk_label_set_text(GTK_LABEL(g_openglTimeLabel), str);

	float loc[48];
	string con;

	con = g_polhemusConnected ? string("connected\n") : string("disconnected\n");
	if (g_polhemus) {
		g_polhemus->getLoc(gettime(), loc);

		ostringstream oss;
		oss << std::setprecision(2);
		oss << std::fixed;
		int nsensors = g_polhemus->m_nsensors;
		float *ff = loc;
		auto clampfloat = [&](float w) {
			return fabs(w) > 1e6 ? 0 : w;;
		};
		for (int j=0; j<nsensors; j++) {
			oss << "marker_" << (j+1) << " ";
			oss << " x:" << clampfloat(*ff++);
			oss << " y:" << clampfloat(*ff++);
			oss << " z:" << clampfloat(*ff++) << "\n";
			//ff += 3;
		}
		con += oss.str();
	}
	gtk_label_set_text(GTK_LABEL(g_polhemusLabel), con.c_str());

#ifdef OPTO
	if (g_opto)
		g_opto->getLoc(gettime(), loc);
	con  = g_optoConnected ? string("connected\n") : string("disconnected\n");
	con += g_optoLabelStr;
	gtk_label_set_text(GTK_LABEL(g_optoLabel), con.c_str());
#else
	gtk_label_set_text(GTK_LABEL(g_optoLabel), "disabled in build.");
#endif

#ifdef LABJACK
	gtk_label_set_text(GTK_LABEL(g_labjackLabel), g_labjackLabelStr.c_str());
#else
	gtk_label_set_text(GTK_LABEL(g_labjackLabel), "disabled in build.");
#endif

	return TRUE;
}
string getMmapStructure()
{
	std::stringstream oss;
	oss << "% mmap structure (pass to bmi5_mmap())\n";
	oss << "mex -O " << g_basedirname << "/matlab/bmi5_mmap.cpp % to make sure you have the latest version.\n";
	oss << "clear b5; \n";
	for (unsigned int i=0; i<g_objs.size(); i++) {
		oss << g_objs[i]->getStructInfo();
	}
	oss << "b5_numdoubles = 0;\n";
	oss << "b5c = struct2cell(b5);\n";
	oss << "for i=1:size(b5c)\n";
	oss << "\tb5_numdoubles = b5_numdoubles + numel(b5c{i});\n";
	oss << "end\n clear b5c;\n b5_numdoubles\n";
	return oss.str();
}
static void printMmapStructure(GtkWidget *, gpointer )
{
	//print the relevant matlab mmap infos.
	string s = getMmapStructure();
	printf("%s", s.c_str());
}
static void fullscreenCB(GtkWidget *w, gpointer p)
{
	GtkWindow *top = GTK_WINDOW(p);
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)))
		gtk_window_fullscreen(top);
	else
		gtk_window_unfullscreen(top);
}
static void stickyCB(GtkWidget *w, gpointer p)
{
	GtkWindow *top = GTK_WINDOW(p);
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)))
		gtk_window_stick(top);
	else
		gtk_window_unstick(top);
}
static void vsyncCB(GtkWidget *w, gpointer)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)))
		g_glvsync = true;
	else
		g_glvsync = false;
}
static void opViewCB(GtkWidget *w, gpointer)
{
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w)))
		g_renderOpView = true;
	else
		g_renderOpView = false;
}
void flush_pipe(int fid)
{
	fcntl(fid, F_SETFL, O_NONBLOCK);
	char *d = (char *)malloc(1024*8);
	int r = read(fid, d, 1024*8);
	printf("flushed %d bytes\n", r);
	free(d);
	int opts = fcntl(fid,F_GETFL);
	opts ^= O_NONBLOCK;
	fcntl(fid, F_SETFL, opts);
}
/* matlab interaction -- through shared memory. */
void *mmap_thread(void *)
{
	size_t length = 8*1024*8; //mmapFileSize(g_objs);

	mmapHelp mmh(length, g_mmap.c_str());
	mmh.prinfo();

	fifoHelp pipe_in(g_in_fifo.c_str());
	pipe_in.prinfo();

	fifoHelp pipe_out(g_out_fifo.c_str());
	pipe_out.prinfo();

	char buf[256];
	int bufn = 0;
	flush_pipe(pipe_out.m_fd);
	int code = 0;
	while (!g_die) {
		//printf("%d waiting for matlab...\n", frame);
		int r = read(pipe_in.m_fd, &(buf[bufn]), 256);
		if (r > 0) bufn += r;
		buf[bufn] = 0;
		//printf("%d read %d %s\n", frame, r, buf);
		if (r >= 3 && buf[0] == 'g' && buf[1] == 'o') {
			//react to changes requested.
			g_matlabTimer.exit();
			double *b = (double *)mmh.m_addr;
			pthread_mutex_lock(&mutex_gobjs);
			for (unsigned int i=0; i<g_objs.size(); i++)
				b = g_objs[i]->mmapRead(b);
			//add alignment check.
			int count = (int)((long long)b - (long long)mmh.m_addr);
			count /= 8;
			*b = (double)count;
			if (g_record) {
				for (unsigned int i=0; i<g_objs.size(); i++)
					g_objs[i]->store(); //store when changes were commanded.
			}
			pthread_mutex_unlock(&mutex_gobjs);
			// variables which are the other direction -- e.g. polhemus --
			// should be stored when *they* are recieved.
			usleep(100); //let the kernel sync memory (required..)
			g_matlabTimer.enter();
			code = 0; // = OK -- matlab waits for this response.
			write(pipe_out.m_fd, (void *)&code, 4);
			bufn = 0;
		} else {
			//setup command?
			pthread_mutex_lock(&mutex_gobjs);
			string txt = string(buf);
			char_separator<char> sep("\", ");
			tokenizer<char_separator<char> > tokens(txt, sep);
			string resp = {""};
			string typ = {""};
			string name = {"null"};
			auto sendResponse = [&](string q) {
				code = q.size();
				write(pipe_out.m_fd, (void *)&code, 4); //this so we know how much to seek in matlab.
				write(pipe_out.m_fd, q.c_str(), q.size());
			};
			auto makeConf = [&](Serialize* obj, string nam) {
				obj->m_name = nam + string("_");
				g_objs.push_back(obj);
				resp = {"made a "};
				resp += typ;
				resp += " named ";
				resp += nam;
				resp += "\n";
			};
			auto makeStoreConf = [&](Serialize * obj, string type, string nam) {
				obj->m_name = nam + string("_");
				g_objs.push_back(obj);
				resp  = {"made a store ("};
				resp += type;
				resp += ") named ";
				resp += nam;
				resp += "\n";
			};
			auto clamp01 = [&](float v) {
				return (v > 1 ? 1 : (v < 0 ? 0 : v));
			};
			auto g_objsRm = [&](Serialize* sx) {
				int j = -1;
				for (unsigned int i=0; i<g_objs.size(); i++) {
					if (g_objs[i] == sx) j = i;
				}
				if (j>=0) g_objs.erase(g_objs.begin()+j);
			};
			auto beg = tokens.begin();
			if ((*beg) == string("make")) {
				beg++;
				if ((*beg) == string("circle")) {
					typ = string("circle");
					beg++;
					name = typ;
					Circle *shp = new Circle(0.5, 64);
					if (beg != tokens.end())
						name = (*beg); //name of the circle.
					makeConf(shp, name);
				} else if ((*beg) == string("ring")) {
					typ = string("ring");
					beg++;
					float thick = 0.2;
					name = typ;
					if (beg != tokens.end()) {
						name = (*beg);
						beg++;
					}
					if (beg != tokens.end()) {
						thick = clamp01(atof(beg->c_str()));
						beg++;
					}
					Ring *shp = new Ring(0.5*(1-thick), 0.5, 64);
					makeConf(shp, name);
				} else if ((*beg) == string("square")) {
					typ = string("square");
					beg++;
					name = typ;
					if (beg != tokens.end()) {
						name = (*beg); // name of the square.
						beg++;
					}
					Square *shp = new Square(1.f);
					makeConf(shp, name);
				} else if ((*beg) == string("open_square")) {
					typ = string("open_square");
					beg++;
					float thick = 0.2;
					name = typ;
					if (beg != tokens.end()) {
						name = (*beg); // name of the open square
						beg++;
					}
					if (beg != tokens.end()) {
						thick = clamp01(atof(beg->c_str()));
						beg++;
					}
					OpenSquare *shp = new OpenSquare(1.f-thick, 1.f);
					makeConf(shp, name);
				} else if ((*beg) == string("stars")) {
					typ = string("stars");
					beg++;
					name = typ;
					int numstars = 3000;
					if (beg != tokens.end()) {
						name = (*beg);
						beg++;
						if (beg != tokens.end()) {
							numstars = abs(atoi(beg->c_str()));	// negatives not allowed
							beg++;
						}
					}
					StarField *sf = new StarField();
					sf->makeStars(numstars);
					makeConf(sf, name);
				} else if ((*beg) == string("stars_circle")) {
					typ = string("stars_circle");
					beg++;
					name = typ;
					int numstars = 3000;
					if (beg != tokens.end()) {
						name = (*beg);
						beg++;
						if (beg != tokens.end()) {
							numstars = abs(atoi(beg->c_str()));	// negatives not allowed
							beg++;
						}
					}
					StarFieldCircle *sf = new StarFieldCircle();
					sf->makeStars(numstars);
					makeConf(sf, name);
				} else if ((*beg) == string("text")) {
					typ = string("text");
					beg++;
					name = typ;
					int nchars = 256;
					if (beg != tokens.end()) {
						name = (*beg);
						beg++;
						if (beg != tokens.end()) {
							nchars = abs(atoi(beg->c_str()));	// negatives not allowed
							beg++;
						}
					}
					DisplayText *x = new DisplayText(nchars);
					makeConf(x, name);
				} else if ((*beg) == string("tone")) {
					// make tone <name>
					// add a tone-interpreter (can add multiple for polyphony)
					typ = string("tone");
					beg++;
					name = typ;
					if (beg != tokens.end()) {
						name = (*beg);
						beg++;
					}
					ToneSerialize *tsz = new ToneSerialize();
					makeConf(tsz, name);
				} else if (*beg == string("store")) {
					// make store <type> <size> <name>
					typ = string("store");
					beg++;
					name = typ;
					string error = {"could not interpret command --\n"};
					error += {"format is: store <type> <size> <name>"};
					string typedesc = {"type needs to be one of:\n"};
					typedesc += {"char, uchar, int, float, double\n"};
					if (beg != tokens.end()) {
						string type = *beg++;
						if (beg != tokens.end()) {
							string ssize = *beg++;
							int size = atoi(ssize.c_str());
							if (beg != tokens.end() && size > 0 && size < 1024) {
								name = (*beg++);
								//good, we have all the parameters
								if (type == string("char")) {
									VectorSerialize<char> *obj =
									    new VectorSerialize<char>(size, MAT_C_INT8);
									makeStoreConf(obj, type, name);
								} else if (type == string("uchar")) {
									VectorSerialize<unsigned char> *obj =
									    new VectorSerialize<unsigned char>(size, MAT_C_UINT8);
									makeStoreConf(obj, type, name);
								} else if (type == string("int")) {
									VectorSerialize<int> *obj =
									    new VectorSerialize<int>(size, MAT_C_INT32);
									makeStoreConf(obj, type, name);
								} else if (type == string("float")) {
									VectorSerialize<float> *obj =
									    new VectorSerialize<float>(size, MAT_C_SINGLE);
									makeStoreConf(obj, type, name);
								} else if (type == string("double")) {
									VectorSerialize<double> *obj =
									    new VectorSerialize<double>(size, MAT_C_DOUBLE);
									makeStoreConf(obj, type, name);
								} else {
									resp = {"could not generate a store --\n"};
									resp += typedesc;
								}
							} else resp = error + typedesc;
						} else resp = error + typedesc;
					} else resp = error + typedesc;
				} else if (*beg == string("polhemus")) {
					// make polhemus
					// (or)
					// make polhemus <name>
					// (or)
					// make polhemus <name> <nsensors>
					if (g_polhemusConnected) {
						typ = string("polhemus");
						beg++;
						name = typ;
						if (beg != tokens.end()) {
							name = (*beg);
							beg++;
						}
						int nsensors = 1;
						if (beg != tokens.end()) {
							nsensors = atoi(beg->c_str());
							beg++;
						}
						g_objsRm(g_polhemus);
						if (g_polhemus)
							delete g_polhemus;
						nsensors = nsensors < 1 ? 1 : (nsensors > 8 ? 8 : nsensors);
						g_polhemus = new PolhemusSerialize(nsensors);
						makeConf(g_polhemus, name);
					} else {
						resp = string("could not initialize polhemus object ");
						resp += string(" -- not connected.\n");
					}
				} else if (*beg == string("mouse")) {
					// make mouse <name> -- simple mouse control.
					typ = string("mouse");
					beg++;
					name = typ;
					if (beg != tokens.end()) {
						name = *beg;
						beg++;
					}
					g_objsRm(g_mouse);
					if (g_mouse) delete g_mouse;
					g_mouse = new MouseSerialize();
					makeConf(g_mouse, name);
				} else if (*beg == string("optotrak")) {
					// optotrak <name> <nsensors> -- definitely more options later!
					if (g_optoConnected) {
						typ = string("optotrak");
						beg++;
						name = typ;
						if (beg != tokens.end()) {
							name = *beg;
							beg++;
						}
						int nsensors = 1;
						if (beg != tokens.end()) {
							nsensors = atoi(beg->c_str());
							beg++;
						}
						g_objsRm(g_opto);
						if (g_opto)
							delete g_opto;
						nsensors = nsensors < 1 ? 1 : (nsensors > 10 ? 10 : nsensors);
						g_opto = new OptoSerialize(nsensors);
						makeConf(g_opto, name);
					} else {
						resp = string("could not initialize optotrack object ");
						resp += string(" -- not connected.\n");
					}
				} else if (*beg == string("tdtudp")) {
					// make tdtudp <name> <size> <ipaddress>
					typ = string("tdtudp");
					beg++;
					name = typ;
					resp  = string("could not interpret command --\n");
					resp += "format is tdtudp <name> <size> <ipaddress>\n";
					if (beg != tokens.end()) {
						name = *beg;
						beg++;
					}
					if (beg != tokens.end()) {
						string ssize = *beg++;
						int size = atoi(ssize.c_str());
						if (beg != tokens.end() && size > 0 && size < 256) {
							string ipaddr = *beg++;
							int sock = openSocket((char *)ipaddr.c_str(), LISTEN_PORT);
							if (sock == 0) {
								resp = string("could not open socket to ") + ipaddr;
							} else {
								if (!checkRZ(sock)) {
									resp = string("there does not seem to be an RZ2 at")+ipaddr;
								} else {
									TdtUdpSerialize *obj = new TdtUdpSerialize(sock, size);
									makeConf(obj, name);
									resp = string("successfully made a UDP connection object to")+ipaddr;
								}
							}
						}
					}
				} else if (*beg == string("labjack")) {
					// make labjack <name> <number of analog inputs> <number of digital outputs>
					if (g_labjackConnected) {
						typ = string("labjack");
						beg++;
						name = typ;
						if (beg != tokens.end()) {
							name = (*beg);
							beg++;
						}
						int nsensors = 1;
						int nchannels = 1;
						if (beg != tokens.end()) {
							nsensors = atoi(beg->c_str());
							beg++;
						}
						if (beg != tokens.end()) {
							nchannels = atoi(beg->c_str());
							beg++;
						}
						g_objsRm(g_labjack_AIN);
						g_objsRm(g_labjack_DOUT);
						if (g_labjack_AIN)
							delete g_labjack_AIN;
						if (g_labjack_DOUT)
							delete g_labjack_DOUT;
						nsensors = nsensors < 1 ? 1 : (nsensors > 8 ? 8 : nsensors);
						nchannels = nchannels < 1 ? 1 : (nchannels > 8 ? 8 : nchannels);
						g_labjack_AIN = new LabjackSerializeAIN(nsensors);
						g_labjack_DOUT = new LabjackSerializeDOUT(nchannels);
						makeConf(g_labjack_AIN, name + string("AIN"));
						makeConf(g_labjack_DOUT, name + string("DOUT"));
					} else {
						resp = string("could not initialize labjack object ");
						resp += string(" -- not connected.\n");
					}
				}
			} else if (*beg == string("mmap")) {
				// return the mmapinfo.
				resp = getMmapStructure();
			} else if (*beg == string("clear_all")) {
				printf("clearing all data in memory\n");
				for (unsigned int i=0; i<g_objs.size(); i++)
					g_objs[i]->clear();
				resp = {"cleared all stored data\n"};
			} else if (*beg == string("delete_all")) {
				printf("deleting all objects\n");
				//prevent dangling pointers -- these all can be deleted through g_objs
				if (g_polhemus) g_polhemus = 0;
				if (g_mouse) g_mouse = 0;
				if (g_opto) g_opto = 0;
				if (g_labjack_AIN) g_labjack_AIN = 0;
				if (g_labjack_DOUT) g_labjack_DOUT = 0;
				for (unsigned int i=0; i<g_objs.size(); i++) {
					delete g_objs[i];
				}
				resp = {"all objects deleted.\n"};
				g_objs.clear();
				gobjsInit(); //timing, etc.
			} else if (*beg == string("save")) {
				beg++;
				if (beg != tokens.end()) {
					string fname = *beg;
					pthread_mutex_lock(&mutex_fwrite);
					writeMatlab(g_objs, (char *)fname.c_str(), false);
					pthread_mutex_unlock(&mutex_fwrite);
					resp = string("saved file ");
					resp += fname;
					resp += {"\n"};
				}
			} else if (*beg == string("start_recording")) {
				beg++;
				g_record = true;
				resp = string("started recording.");
			} else if (*beg == string("stop_recording")) {
				beg++;
				g_record = false;
				resp = string("stopped recording.");
			} else {
				resp = {"Current command vocabulary:\n"};
				resp += {"\tmake circle <name>\n"};
				resp += {"\tmake ring <name> <frac thickness>\n"};
				resp += {"\tmake square <name>\n"};
				resp += {"\tmake open_square <name> <frac thickness>\n"};
				resp += {"\tmake stars <name> <num stars>\n"};
				resp += {"\tmake stars_circle <name> <num stars>\n"};
				resp += {"\tmake text <name> <nchars>\n"};
				resp += {"\t\tDisplays text on the screen.\n"};
				resp += {"\t\tnchars should be less than 256\n"};
				resp += {"\t\t<name>_v in b5 structure MUST NOT CHANGE SIZE.\n"};
				resp += {"\t\te.g. you cannot only do b5.text_v = 'something';\n"};
				resp += {"\t\tdo: b5.text_v = [double(msg) zeros(1,nchars-length(msg))]';"};
				resp += {"\tmake tone <name>\n"};
				resp += {"\t\tmake a tone generator\n"};
				resp += {"\tmake store <type> <size> <name>\n"};
				resp += {"\t\tmake a generic store for matlab data --\n"};
				resp += {"\t\t<type> can be char, uchar, int, float, or double.\n"};
				resp += {"\t\t<size> is the size of the vector\n"};
				resp += {"\t\tNOTE: in b5, all vectors are type DOUBLE,\n"};
				resp += {"\t\tindependent of disc storage type\n"};
				resp += {"\tmake polhemus <name> [<nsensors>]-- for getting polhemus sensor loc\n"};
				resp += {"\tmake mouse <name> -- for getting mouse location\n"};
				resp += {"\tmake optotrak <name> [<nsensors>] -- for getting optotrak location\n"};
				resp += {"\tmake labjack <name> [<nsensors>] -- for getting analog input\n"};
				resp += {"\tmake tdtudp <name> <size> <ipaddress> -- for talking to TDT\n"};
				resp += {"\tmmap\n"};
				resp += {"\t\treturn mmap structure information, for eval() in matlab\n"};
				resp += {"\tclear_all\n"};
				resp += {"\t\tclear data stored in memory (e.g. when starting an experiment)\n"};
				resp += {"\tdelete_all\n"};
				resp += {"\t\tdelete all objects (shapes etc) & reinstate timing objects.\n"};
				resp += {"\tstart_recording\n"};
				resp += {"\tstop_recording\n"};
				resp += {"\tsave <file name>\n"};
			}
			pthread_mutex_unlock(&mutex_gobjs);
			sendResponse(resp);
			usleep(200000); //does not seem to limit the frame rate, just the startup sync.
			bufn = 0;
		}
		g_nCommand++;
	}
	return NULL;
}
void *backup_thread(void *)
{
	//find a directory, see if it exist; if not make it.
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	bool found = true;
	char dirname[256];
	int i = 1;
	while (found) {
		snprintf(dirname, 256, "%s/%04d-%02d-%02d_%04d",
		         g_backup_dir.c_str(), tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, i);
		struct stat st;
		int err = stat(dirname, &st);
		if (!S_ISDIR(st.st_mode) || err < 0) {
			found = false;
			if (mkdir(dirname, 0777)) {
				printf("could not mkdir %s\n", dirname);
				g_do_backup = false;
			}
		} else i++;
	}
	int k=1;
	while (!g_die) {
		for (int j=0; j<10 && !g_die; j++)
			sleep(1); //so it closes somewhat quickly.
		if (!g_die && g_do_backup && matlabHasNewData(g_objs)) {
			char fname[256];
			snprintf(fname, 256, "%s/backup_%04d.mat", dirname, k);
			pthread_mutex_lock(&mutex_fwrite);
			writeMatlab(g_objs, fname, true);
			pthread_mutex_unlock(&mutex_fwrite);
			printf("... saved %s\n", fname);
			k++;
		}
	}
	return 0;
}
/* Liberty / Polhemus.
 as reading from USB / serial will take some time, it makes sense to
 put this in a separate thread, with mutex so that the instant the data is
 available we pass it through the task logic & display on screen
 (or control microstimulation).
 There seems no other way to get lower latency ...
 While writing floats is likely atomic, writing three floats is not --
 hence the need for interlock.
 */
#define BUF_SIZE 1000
char g_circBuff[1024];
unsigned int g_cbPtr = 0;	// write pointer
unsigned int g_cbRN = 0; 	// pointer to the last carrige return (read pointer).

void *polhemus_thread(void *)
{
	unsigned char buf[BUF_SIZE];
	int count, len, i;

	//init the communication obj.
	polhemus *pol = new polhemus();
	if (!pol) {
		printf("Memory Allocation Error creating tracker object\n");
		return NULL;
	}
	int fail;
	//fail = pol->UsbConnect(TRKR_LIB); //see polhemus.h
	fail = pol->Rs232Connect(g_polhemus_serial.c_str(), 115200);
	if (fail) {
		printf("could not open via rs232 to Polhemus on %s\n", g_polhemus_serial.c_str());
		printf("> try sudo usermod -a -G dialout <username>");
		printf("> then logout and log back in.");
		g_polhemusConnected = false;
	} else {
		printf("connecting to polhemus via rs232 on %s\n", g_polhemus_serial.c_str());
		g_polhemusConnected = true;
	}
	//flush the buffer, sync things up.

	pol->Write("O*,2\r"); // turn off Euler angles (no response is sent).
	usleep(5e4);

	count = 0;
	int rxbytes = 0;
	do {
		pol->Write("p"); // request position data (and stop continuous...)
		usleep(5e4); // 5e4 us is way way slower than polhemus should be able to handle
		len = pol->Read(buf,BUF_SIZE);  // keep trying till we get a response
		rxbytes += len > 0 ? len : 0;
		count++;
		//if (len > 0) printf("%.*s\n", len, buf); else printf("NO DATA!\n");
	} while (count < 10);

	if (rxbytes <= 0) {
		g_polhemusConnected = false;
		cout << "polhemus: could not connect." << endl;
	} else {
		cout << "polhemus: connection established .." << endl;
		// first establish comm and clear out any residual trash data
		double frames = 0;
		float markerData[16*3];

		pol->Write("U1\r"); // put polhemus in centimeter mode (no response is sent)
		usleep(5e4);

		// we only care about x, y, z -- faster (lower latency) transmission.
		pol->Write("O*,2\r"); // turn off Euler angles (no response is sent).
		usleep(5e4);

		// now put it in binary (faster than ascii!) mode
		pol->Write("f1\r"); // no response is sent
		usleep(5e4);

		pol->Write("c\r"); // request continuous data.
		usleep(5e4);

		// and read the data in a loop.
		g_cbPtr = g_cbRN = 0;
		while (!g_die) {
			count = 0;
			memset(buf, 0, 16*20); // max markers * 20 bytes. is this necessasry???
			do {
				len = pol->Read(buf+count, BUF_SIZE-count);
				if (len>0)
					count+=len;
				usleep(300);
			} while ((len>0));
			if (count > 0) {
				//frame starts with 'LY_P', and is 8 bytes. This is followed by 3 4-byte floats.
				//total frame is hence 20 bytes.
				for (i=0; i<count; i++) {
					g_circBuff[g_cbPtr % 1024] = buf[i];
					g_cbPtr++;
				}
				// align to frame.
				while (((g_circBuff[g_cbRN % 1024] != 'L') ||
				        (g_circBuff[(g_cbRN+1) % 1024] != 'Y')) &&
				       (g_cbRN + 20 <= g_cbPtr)) {
					g_cbRN++;
				}
				//printf("polhemus lag: %d\n", g_cbPtr - g_cbRN);
				//this will either leave us aligned at the start of a frame
				//or waiting for more data.
				//copy between the current /r/n.
				while (g_circBuff[g_cbRN % 1024] == 'L' &&
				       g_circBuff[(g_cbRN+1) % 1024] == 'Y' &&
				       g_cbRN + 20 <= g_cbPtr) {

					int markerid = (int)g_circBuff[(g_cbRN+2) % 1024]; // convert to int

					if (!g_polhemus) {
						g_cbRN += 20;
						continue;
					}

					if (markerid < 1 || markerid > g_polhemus->m_nsensors) {
						g_cbRN += 20;
						continue;
					}

					for (i=0; i<20 && (g_cbRN+i) < g_cbPtr; i++) {
						buf[i] = g_circBuff[(g_cbRN+i) % 1024];
					}
					buf[i] = 0; // not sure why we need to do this? xxx
					// this data is used, move the pointer forward one frame
					g_cbRN += 20;
					float *pData=(float *)(buf+8);			// header is first 8 bytes
					if (g_polhemus && g_record) {
						for (int j=0; j<3; j++)
							markerData[(markerid-1)*3 + j] = pData[j];
						if (markerid ==  g_polhemus->m_nsensors)
							g_polhemus->store(markerData);
					}
					frames += 1;
					usleep(1800);
				}
			}
		}
		printf("polhemus: stopping continuous mode.\n");

		pol->Write("f0\r"); // ascii mode (no response is sent)
		usleep(5e4);

		do {
			pol->Write("p"); // stop continuous mode.
			usleep(5e4);
			len = pol->Read(buf, BUF_SIZE); // throw away.
			count++;
			//if (len > 0) printf("%.*s\n", len, buf); else printf("NO DATA!\n");
		} while (count < 10);

		//pol->Write("\x19\r"); // send the reset command ^Y
		//usleep(1e4);
		//len = pol->Read(buf, BUF_SIZE); //throw away.
	}
	pol->Close();
	return NULL;
}

#ifdef OPTO
void *opto_thread(void *)
{
	pcap_t *handle;			/* Session handle */
	char dev[PCAP_ERRBUF_SIZE];			/* The device to sniff on */
	char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
	struct bpf_program fp;		/* The compiled filter */
	char filter_exp[] = "src port 10000";	/* The filter expression */
	bpf_u_int32 mask;		/* Our netmask */
	bpf_u_int32 net;		/* Our IP */
	struct pcap_pkthdr header;	/* The header that pcap gives us */
	const u_char *packet;		/* The actual packet */
	int j, k, len;
	/* ethernet headers are always exactly 14 bytes */
#define SIZE_ETHERNET 14
	const struct sniff_ip *ip; /* The IP header */
	const struct sniff_tcp *tcp; /* The TCP header */
	const unsigned char *payload; /* Packet payload */

	u_int size_ip;
	u_int size_tcp;
	unsigned int *u;
	float *f;

	/* Define the device */
	strcpy(dev, "eth1");
	/* Find the properties for the device */
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		fprintf(stderr, "Optotrak: Couldn't get netmask for device %s: %s\n", dev, errbuf);
		net = 0;
		mask = 0;
		return (void *)2;
	} else {
		printf("Optotrak: eth1 net %x mask %x\n", net, mask);
	}
	/* Open the session in promiscuous mode */
	handle = pcap_open_live(dev, 1024, 1, 5, errbuf); //second to last argument: timeout, ms
	if (handle == NULL) {
		fprintf(stderr, "Optotrak: Couldn't open device %s: %s\n", "eth1", errbuf);
		fprintf(stderr, "\t\ttry 'make opto' to set permissions.\n");
		return (void *)2;
	}
	/* Compile and apply the filter */
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
		fprintf(stderr, "Optotrak: Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return (void *)2;
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Optotrak: Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return (void *)2;
	}
	/* Grab a packet */
	int packets = 0;
	float g[32];
	k = 0;
	while (!g_die) {
		packet = pcap_next(handle, &header);
		/* Print its length */
		if (packet) {
			//printf("Jacked a packet with length of [%d]\n", header.len);
			packets++;
			ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
			size_ip = IP_HL(ip)*4;
			//printf("size_ip = %d; tl = %d\n", size_ip, htons(ip->ip_len));
			if (size_ip < 20) {
				fprintf(stderr, "Optotrak:  Invalid IP header length: %u bytes\n", size_ip);
				return (void *)2;
			}
			tcp = (struct sniff_tcp *)(packet + SIZE_ETHERNET + size_ip);
			size_tcp = TH_OFF(tcp)*4;

			if (size_tcp >= 20) {
				g_optoConnected = true;
				k++;
				payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
				u = (unsigned int *)payload;
				f = (float *)payload;
				len = header.len - SIZE_ETHERNET - size_ip - size_tcp;
				if (0) {
					printf("%ld.%ld\t:", header.ts.tv_sec, header.ts.tv_usec);
					for (j=0; j<len; j++) {
						printf("%02x ", *payload++);
					}
					printf("\n");
				}
				if (u[0] == 0x1f && u[1] == 0x050001) {
					k = 0;
				}
				if (k == 1) {
					//printf("timestamp: %d\n", u[1]);
				}
				if (k == 2) {
					ostringstream oss;
					oss << std::setprecision(2);
					oss << std::fixed;
					int nsensors = len/24;
					float *ff = f;
					auto clampfloat = [&](float w) {
						return fabs(w) > 1e6 ? 0 : w;;
					};
					for (j=0; j<nsensors; j++) {
						oss << "marker_" << (j+1) << " ";
						oss << " x:" << clampfloat(*ff++);
						oss << " y:" << clampfloat(*ff++);
						oss << " z:" << clampfloat(*ff++) << "\n";
						ff += 3;
					}
					g_optoLabelStr = oss.str();
					if (g_opto) {
						//assume (for Certus) there is no orientation data.
						int m = 0;
						for (j=0; j<(len/4); j++) {
							if ((j % 6) < 3) {
								g[m] = *f;
								m++;
							}
							f++;
						}
						g_opto->store(g);
					}
				}
			} else {
				fprintf(stderr, "Optotrak: Invalid TCP header length: %u bytes\n", size_tcp);
			}
		}
	}
	/* And close the session */
	pcap_close(handle);
	return (void *)0;
}
#endif

#ifdef LABJACK
void *labjack_thread(void *)
{
	const uint8 settlingFactor = 0; //0=5us, 1=10us, 2=100us, 3=1ms, 4=10ms.  Default 0.
	const uint8 gainIndex = 2; //0 = +-10V, 1 = +-1V, 2 = +-100mV, 3 = +-10mV, 15=autorange.  Default 0.
	const uint8 resolution = 1; //1=default, 1-8 for high-speed ADC, 9-13 for high-res ADC on U6-Pro. Default 1.
	const uint8 differential = 1; //Indicates whether to do differential readings.  Default 0 (false).
	g_labjackLabelStr = string("disconnected");
	/// init the USB device.
	HANDLE hDevice = 0;
	u6CalibrationInfo caliInfo;
	int numAINChannels = 0;
	int numDOUTChannels = 0;
	uint8 *sendBuff=0, *recBuff=0;
	//Opening first found U6 over USB
	if ( (hDevice = openUSBConnection(-1)) == NULL )
		return 0;
	//Get calibration information from U6
	if ( getCalibrationInfo(hDevice, &caliInfo) < 0 ) {
		closeUSBConnection(hDevice);
		return 0;
	}
	g_labjackConnected = true;
	g_labjackLabelStr = string("connected, unconfigured");
	/// wait for configuration through matlab.
	while (!g_die && numAINChannels == 0 && numDOUTChannels == 0) {
		if (g_labjack_AIN && g_labjack_DOUT) {
			numAINChannels = g_labjack_AIN->m_nsensors;
			numDOUTChannels = g_labjack_DOUT->m_nchannels;
		}
		if (!numAINChannels && !numDOUTChannels) sleep(1);
	}
	if (numAINChannels > 0 && numDOUTChannels > 0) {
		/// setup the feedback command.
		uint16 checksumTotal, bits16;
		uint32 bits32;

		int sendChars, recChars, i, j, sendSize, recSize;
		float valueAIN[14];
		float valueDOUT[14];

		for ( i = 0; i < 14; i++ )
			valueAIN[i] = 9999;

		for ( i = 0; i < 14; i++)
			valueDOUT[i] = 0;

		//Setting up a Feedback command that will set CIO0-3 as input, and
		//set DAC0 voltage
		sendBuff = (uint8 *)malloc(18*sizeof(uint8));  //Creating an array of size 18
		recBuff = (uint8 *)malloc(10*sizeof(uint8));   //Creating an array of size 10

		sendBuff[1] = (uint8)(0xF8);  //Command byte
		sendBuff[2] = 6;              //Number of data words (.5 word for echo, 5.5
		//words for IOTypes and data)
		sendBuff[3] = (uint8)(0x00);  //Extended command number

		sendBuff[6] = 0;    //Echo
		sendBuff[7] = 29;   //IOType is PortDirWrite
		sendBuff[8] = 0;    //Writemask (for FIO)
		sendBuff[9] = 0;    //Writemask (for EIO)
		sendBuff[10] = 15;  //Writemask (for CIO)
		sendBuff[11] = 0;   //Direction (for FIO)
		sendBuff[12] = 0;   //Direction (for EIO)
		sendBuff[13] = 0;   //Direction (for CIO)

		//Setting DAC0 with 2.5 volt output
		sendBuff[14] = 38;    //IOType is DAC0(16-bit)

		//Value is 2.5 volts (in binary)
		getDacBinVoltCalibrated16Bit(&caliInfo, 0, 2.5, &bits16);
		sendBuff[15] = (uint8)(bits16&255);
		sendBuff[16] = (uint8)(bits16/256);

		sendBuff[17] = 0;  //extra padding byte

		extendedChecksum(sendBuff, 18);

		//Sending command to U6
		if ( (sendChars = LJUSB_Write(hDevice, sendBuff, 18)) < 18 ) {
			if (sendChars == 0)
				printf("Feedback (CIO input) error : write failed\n");
			else
				printf("Feedback (CIO input) error : did not write all of the buffer\n");
			goto cleanmem;
		}
		//Reading response from U6
		if ( (recChars = LJUSB_Read(hDevice, recBuff, 10)) < 10 ) {
			if ( recChars == 0 ) {
				printf("Feedback (CIO input) error : read failed\n");
				goto cleanmem;
			} else
				printf("Feedback (CIO input) error : did not read all of the buffer\n");
		}
		checksumTotal = extendedChecksum16(recBuff, 10);
		if ( (uint8)((checksumTotal / 256) & 0xff) != recBuff[5] ) {
			printf("Feedback (CIO input) error : read buffer has bad checksum16(MSB)\n");
			goto cleanmem;
		}
		if ( (uint8)(checksumTotal & 0xff) != recBuff[4] ) {
			printf("Feedback (CIO input) error : read buffer has bad checksum16(LBS)\n");
			goto cleanmem;
		}
		if ( extendedChecksum8(recBuff) != recBuff[0] ) {
			printf("Feedback (CIO input) error : read buffer has bad checksum8\n");
			goto cleanmem;
		}
		if ( recBuff[1] != (uint8)(0xF8) || recBuff[3] != (uint8)(0x00) ) {
			printf("Feedback (CIO input) error : read buffer has wrong command bytes \n");
			goto cleanmem;
		}
		if ( recBuff[6] != 0 ) {
			printf("Feedback (CIO input) error : received errorcode %d for frame %d in Feedback response. \n", recBuff[6], recBuff[7]);
			goto cleanmem;
		}

		free(sendBuff);
		free(recBuff);

		//Setting up Feedback command that will run infinity times.
		if ( ((sendSize = 7+numAINChannels*4) % 2) != 0 )
			sendSize++;
		sendBuff = (uint8 *)malloc(sendSize*sizeof(uint8)); //Creating an array of size sendSize

		if ( ((recSize = 9+numAINChannels*3) % 2) != 0 )
			recSize++;
		recBuff = (uint8 *)malloc(recSize*sizeof(uint8));  //Creating an array of size recSize

		sendBuff[1] = (uint8)(0xF8);     //Command byte
		sendBuff[2] = (sendSize - 6)/2;  //Number of data words
		sendBuff[3] = (uint8)(0x00);     //Extended command number

		sendBuff[6] = 0;     //Echo

		//Setting AIN read commands
		for ( j = 0; j < numAINChannels; j++ ) {
			sendBuff[7 + j*4] = 2;     //IOType is AIN24

			//Positive Channel (bits 0 - 4), LongSettling (bit 6) and QuickSample (bit 7)
			sendBuff[8 + j*4] = j; //Positive Channel
			sendBuff[9 + j*4] = (uint8)(resolution&15) + (uint8)((gainIndex&15)*16);   //ResolutionIndex(Bits 0-3), GainIndex(Bits 4-7)
			sendBuff[10 + j*4] = (uint8)(settlingFactor&7);  //SettlingFactor(Bits 0-2)
			if ( j%2 == 0 )
				sendBuff[10 + j*4] += (uint8)((differential&1)*128);   //Differential(Bits 7)
		}
		extendedChecksum(sendBuff, sendSize);
		ostringstream oss;
		oss << "connected, " << g_labjack_AIN->m_nsensors << " AIN, " << g_labjack_DOUT->m_nchannels << " DOUT\n";
		oss << "green status light should be blinking.";
		g_labjackLabelStr = oss.str();

		i=0;
		while (!g_die) {
			//Sending command to U6
			if ( (sendChars = LJUSB_Write(hDevice, sendBuff, sendSize)) < sendSize ) {
				if (sendChars == 0)
					printf("Feedback error (Iteration %d): write failed\n", i);
				else
					printf("Feedback error (Iteration %d): did not write all of the buffer\n", i);
				goto cleanmem;
			}
			//Reading response from U6
			if ( (recChars = LJUSB_Read(hDevice, recBuff, recSize)) < recSize ) {
				if ( recChars == 0 ) {
					printf("Feedback error (Iteration %d): read failed\n", i);
					goto cleanmem;
				}
			}
			checksumTotal = extendedChecksum16(recBuff, recChars);
			if ( (uint8)((checksumTotal / 256) & 0xff) != recBuff[5] ) {
				printf("Feedback error (Iteration %d): read buffer has bad checksum16(MSB)\n", i);
				goto cleanmem;
			}
			if ( (uint8)(checksumTotal & 0xff) != recBuff[4] ) {
				printf("Feedback error (Iteration %d): read buffer has bad checksum16(LBS)\n", i);
				goto cleanmem;
			}
			if ( extendedChecksum8(recBuff) != recBuff[0] ) {
				printf("Feedback error (Iteration %d): read buffer has bad checksum8\n", i);
				goto cleanmem;
			}
			if ( recBuff[1] != (uint8)(0xF8) || recBuff[3] != (uint8)(0x00) ) {
				printf("Feedback error (Iteration %d): read buffer has wrong command bytes \n", i);
				goto cleanmem;
			}
			if ( recBuff[6] != 0 ) {
				printf("Feedback error (Iteration %d): received errorcode %d for frame %d in Feedback response. \n", i, recBuff[6], recBuff[7]);
				goto cleanmem;
			}
			if ( recChars != recSize ) {
				printf("Feedback error (Iteration %d): received packet if %d size when expecting %d\n", i, recChars, recSize);
				goto cleanmem;
			}

			//Getting AIN voltages
			for (j = 0; j < numAINChannels; j++) {
				double d = 0.0;
				bits32 = recBuff[9+j*3] + recBuff[10+j*3]*256 + recBuff[11+j*3]*65536;
				getAinVoltCalibrated(&caliInfo, resolution, gainIndex, 1, bits32, &d);
				valueAIN[j] = d;
				j = j + differential;
			}
			// copy over the data!
			if (g_labjack_AIN) {
				g_labjack_AIN->store(valueAIN);
			}

			//Setting DOUT values
			if (g_labjack_DOUT) {
				for ( j = 0; j < numDOUTChannels; j++) {
					valueDOUT[j] = g_labjack_DOUT->m_stor[j];
				}
			}
			for ( j = 0; j < numDOUTChannels; j++) {
				if (eDO(hDevice, long(j), long(valueDOUT[j])))
					printf("Error writing DOUT (iteration %d)",i);
			}
			usleep(200); // could be longer, really.
			i++;
		}
	}
cleanmem:
	if (sendBuff) free(sendBuff);
	if (recBuff) free(recBuff);
	printf("labjack: closing USB handle\n");
	closeUSBConnection(hDevice);
	g_labjackLabelStr = string("Error!  Disconnected.\nTry unplugging the labjack\nand restarting bmi5.");
	return 0;
}
#endif

static void saveMatlabData(gpointer, gpointer parent_window)
{
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Save Data File",
	                                      (GtkWindow *)parent_window,
	                                      GTK_FILE_CHOOSER_ACTION_SAVE,
	                                      "_Cancel", GTK_RESPONSE_CANCEL,
	                                      "_Save", GTK_RESPONSE_ACCEPT,
	                                      NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(
	    GTK_FILE_CHOOSER (dialog), TRUE);
	gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog),"data.mat");
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		pthread_mutex_lock(&mutex_fwrite);
		writeMatlab(g_objs, filename, false);
		pthread_mutex_unlock(&mutex_fwrite);
		g_free (filename);
	}
	gtk_widget_destroy (dialog);
}
static void clearDataCB(gpointer, gpointer parent_window)
{
	//pop up a yes/no (message) dialog.
	GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW(parent_window),
	                    GTK_DIALOG_DESTROY_WITH_PARENT,
	                    GTK_MESSAGE_QUESTION,
	                    GTK_BUTTONS_YES_NO,
	                    "Do you want to clear all recorded data?");

	/* Destroy the dialog when the user responds to it (e.g. clicks a button) */
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_YES) {
		printf("clearing all data in memory\n");
		for (unsigned int i=0; i<g_objs.size(); i++)
			g_objs[i]->clear();
	}
	gtk_widget_destroy(dialog);
}

void longDoubleTest()
{
	printf("sizeof long double %ld\n", sizeof(long double));
	printf("sizeof double %ld\n", sizeof(double));

	long double ld = 0.0;
	double d = 0.0;
	for (unsigned int i=0; i<100000000; i++) { //one billion!
		ld += 0.001234567;
		d += 0.001234567;
	}
	long double ld2 = (long double)d;
	ld2 -= ld;
	printf("sum ld: %Lf, d: %f difference %Lf\n", ld, d, ld2);
}

void gobjsInit()
{
	g_timeSerialize = new TimeSerialize(); //synchronize with gtkclient_tdt.
	g_frameSerialize = new FrameSerialize();
	g_affine44 = new Matrix44Serialize(string("affine"));
	g_quadratic44 = new Matrix44Serialize(string("quadratic"));
	//4x4 matrices are initalized with the identity matrix = not ok for quadratic.
	for (int i=0; i<4; i++) {
		g_quadratic44->m_x[i+i*4] = 0;
		g_quadratic44->m_cmp[i+i*4] = 0; //to catch the edges.
	}
	g_objs.push_back(g_timeSerialize);
	g_objs.push_back(g_frameSerialize);
	g_objs.push_back(g_affine44);
	g_objs.push_back(g_quadratic44);
}

int main(int argn, char **argc)
{
	(void) signal(SIGINT, destroy);

	pid_t mypid = getpid();

	PROCTAB *pr = openproc(PROC_FILLSTAT);
	proc_t pr_info;
	memset(&pr_info, 0, sizeof(pr_info));
	while (readproc(pr, &pr_info) != NULL) {
		if (!strcmp(pr_info.cmd, "bmi5") && pr_info.tgid != mypid) {
			printf("already running with pid: %d\n", pr_info.tgid);
			return 1;
		}
	}

	srand(time(NULL)); // seed rng

#ifdef DEBUG
	//feenableexcept(FE_DIVBYZERO|FE_INVALID|FE_OVERFLOW);  // Enable (some) floating point exceptions
	feenableexcept(FE_INVALID|FE_OVERFLOW);  // Enable (some) floating point exceptions
#endif

	char linkname[1024];
	char *dname;

	memset(linkname, 0, sizeof(linkname));

	if (readlink("/proc/self/exe", linkname, sizeof(linkname)-1) < 1) {
		perror("readlink");
		exit(EXIT_FAILURE);
	}

	dname = dirname(linkname);
	g_basedirname = dname;

	xdgHandle xdg;
	xdgInitHandle(&xdg);
	char *confpath = xdgConfigFind("bmi5/bmi5.rc", &xdg);
	char *tmp = confpath;
	// confpath is "string1\0string2\0string3\0\0"

	while (*tmp) {
		g_lc.loadConf(tmp);
		tmp += strlen(tmp) + 1;
	}
	if (confpath)
		free(confpath);

	// these happen here for threadsafety
	g_lc.getString("bmi5.mmap", g_mmap);
	g_lc.getString("bmi5.fifoIn", g_in_fifo);
	g_lc.getString("bmi5.fifoOut", g_out_fifo);
	g_lc.getString("polhemus.serialPort", g_polhemus_serial);
	g_do_backup = g_lc.getBool("backup.enable");
	g_lc.getString("backup.dir", g_backup_dir);

	//setup a window with openGL.
	GtkWidget *window;
	GtkWidget *da1, *da2, *paned, *v1, *frame;

	g_startTime = gettime();

	PolhemusPredict *pp = new PolhemusPredict();
	pp->test();
	delete(pp);

	gtk_init (&argn, &argc);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
#ifndef DEBUG
	gtk_window_set_title (GTK_WINDOW (window), "sabes experimental control");
#else
	gtk_window_set_title (GTK_WINDOW (window), "sabes experimental control *** DEBUG ***");
#endif
	gtk_window_set_default_size (GTK_WINDOW (window), g_renderOpView?800:270, 650);

	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add (GTK_CONTAINER (window), paned);

	//left: gui etc.
	v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_size_request(GTK_WIDGET(v1), 270, 650);
	g_timeLabel = gtk_label_new("time: ");
	gtk_container_add (GTK_CONTAINER (v1), g_timeLabel );

	auto makeLabel = [&](const char *frameLbl, const char *dflt) {
		frame = gtk_frame_new(frameLbl);
		gtk_container_set_border_width (GTK_CONTAINER (frame), 5);
		gtk_box_pack_start (GTK_BOX (v1), frame, TRUE, TRUE, 0);
		GtkWidget *tlbl = gtk_label_new(dflt);
		//gtk_misc_set_alignment (GTK_MISC (tlbl), 0, 0);
		gtk_label_set_justify( GTK_LABEL(tlbl), GTK_JUSTIFY_LEFT);
		gtk_container_add (GTK_CONTAINER (frame), tlbl );
		return tlbl;
	};
	g_matlabTimeLabel = makeLabel("Matlab stats", "mean:-- max:--");
	g_openglTimeLabel = makeLabel("OpenGL stats", "mean:-- max:--");
	g_polhemusLabel = makeLabel("Polhemus stats", "x -; y -; z -;");
	g_optoLabel = makeLabel("Optotrak stats", "x -; y -; z -;");
	g_labjackLabel = makeLabel("Labjack", "  ");

	GtkWidget *button = gtk_button_new_with_label ("Write data to disk");
	g_signal_connect(button, "clicked", G_CALLBACK(saveMatlabData), window);
	gtk_box_pack_start(GTK_BOX(v1), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label ("Clear data");
	g_signal_connect(button, "clicked", G_CALLBACK(clearDataCB), window);
	gtk_box_pack_start(GTK_BOX(v1), button, TRUE, TRUE, 0);

	button = gtk_button_new_with_label ("print mmap structure");
	g_signal_connect(button, "clicked", G_CALLBACK(printMmapStructure), 0);
	gtk_box_pack_start(GTK_BOX(v1), button, TRUE, TRUE, 0);

	gtk_paned_add1(GTK_PANED(paned), v1);
	da1 = gtk_drawing_area_new ();
	gtk_paned_add2(GTK_PANED(paned), da1);

	//setup the opengl context for da1.
	//before we do this, tun on FSAA.
	putenv((char *)"__GL_FSAA_MODE=10" ); //http://www.opengl.org/discussion_boards/showthread.php/172000-Programmatically-controlling-level-of-AA
	putenv((char *)"__GL_SYNC_TO_VBLANK=0"); //don't sync to vertical blanking.  individually per window.
	putenv((char *)"__GL_SYNC_DISPLAY_DEVICE=CRT-1"); //sync to this display device. (use nvidia-settings)
	gtk_widget_set_double_buffered (da1, FALSE);
	g_daglx[1] = new gtkglx(da1);

	g_signal_connect (da1, "configure-event",
	                  G_CALLBACK (configure1), (void *)1);
	g_signal_connect (da1, "draw",
	                  G_CALLBACK (draw1), (void *)1);
	g_signal_connect (da1, "realize",
	                  G_CALLBACK (realize1), (void *)1);
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

	GtkWidget *top = gtk_window_new (GTK_WINDOW_TOPLEVEL);
#ifndef DEBUG
	gtk_window_set_title (GTK_WINDOW (top), "subject view");
#else
	gtk_window_set_title (GTK_WINDOW (top), "subject view *** DEBUG ***");
#endif
	gtk_window_set_default_size (GTK_WINDOW (top), 320, 240);
	da2 = gtk_drawing_area_new ();
	gtk_container_add (GTK_CONTAINER (top), da2);
	gtk_widget_set_double_buffered (da2, FALSE);
	g_daglx[0] = new gtkglx(da2);

	g_signal_connect (da2, "configure-event",
	                  G_CALLBACK (configure1), (void *)0);
	g_signal_connect (da2, "draw",
	                  G_CALLBACK (draw1), (void *)0);
	g_signal_connect (da2, "realize",
	                  G_CALLBACK (realize1), (void *)0);
	//in order to receive keypresses, must be focusable!
	//gtk_widget_set_can_focus( da2, TRUE);

	gtk_widget_set_events (da2, GDK_EXPOSURE_MASK
	                       | GDK_LEAVE_NOTIFY_MASK
	                       | GDK_BUTTON_PRESS_MASK
	                       | GDK_POINTER_MOTION_MASK
	                       | GDK_POINTER_MOTION_HINT_MASK);

	gtk_widget_show (da2);

	auto makeCheckbox = [&](const char *lbl, bool ic, GCallback cb) {
		button = gtk_check_button_new_with_label(lbl);
		gtk_box_pack_start (GTK_BOX (v1), button, TRUE, TRUE, 0);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (button), ic ? TRUE:FALSE);
		gtk_widget_show (button);
		g_signal_connect (button, "clicked", cb, (gpointer *)top);
	};

	//add a fullscreen checkbox to the gui.
	makeCheckbox("Fullscreen Subject View", false, G_CALLBACK(fullscreenCB));
	makeCheckbox("Sticky Subject View", false, G_CALLBACK(stickyCB));
	makeCheckbox("sync to Vblank\n(resize window to enact)",
	             g_glvsync, G_CALLBACK(vsyncCB));
	makeCheckbox("Render Operator View\n(needed for mouse control)",
	             g_renderOpView, G_CALLBACK(opViewCB));

	g_signal_connect_swapped (window, "destroy",
	                          G_CALLBACK (destroyGUI), NULL);

	gtk_widget_show (window);
	gtk_widget_show (top);

	//add a refresh timeout.
	g_da[1] = da1; //human
	g_da[0] = da2; //monkey
	g_timeout_add (4, refresh, da1); //250 Hz, approximate.

	g_polhemus = 0;
	g_opto = 0;
	g_labjack_AIN = 0;
	g_labjack_DOUT = 0;
	g_mouse = 0;
	pthread_mutex_lock(&mutex_gobjs);
	gobjsInit();
	pthread_mutex_unlock(&mutex_gobjs);

	//mutexes --
	pthread_mutex_init(&mutex_fwrite, NULL);
	pthread_mutex_init(&mutex_gobjs, NULL);

	pthread_t pthread, mthread, bthread;
	pthread_create(&pthread, NULL, polhemus_thread, NULL);
	pthread_create(&mthread, NULL, mmap_thread, NULL);
	pthread_create(&bthread, NULL, backup_thread, NULL);
#ifdef OPTO
	pthread_t othread;
	pthread_create(&othread, NULL, opto_thread, NULL);
#endif
#ifdef LABJACK
	pthread_t lthread;
	pthread_create(&lthread, NULL, labjack_thread, NULL);
#endif

	g_tsc = new TimeSyncClient(); //tells us the ticks when things happen.

	//jack audio.
#ifdef JACK
	jackInit("bmi5", JACKPROCESS_TONES);
	if (g_lc.getBool("jack.connectFront")) {
		jackConnectFront();
	}
	if (g_lc.getBool("jack.connectCenterSub")) {
		jackConnectCenterSub();
	}
	jackTest();
#endif

	g_mainWindow = (GtkWindow *)window;
	gtk_widget_show_all (window);

	g_record = true;

	gtk_main();	// where everything happens

	// now unwind everything in reverse order

	//save data!!
	writeMatlab(g_objs, (char *)"backup.mat", false); //the whole enchilada.

#ifdef JACK
	jackClose(0);
#endif
#ifdef LABJACK
	pthread_join(lthread,NULL);
#endif
#ifdef OPTO
	pthread_join(othread,NULL);
#endif
	// can't join mthread easily since the read on the pipe is blocking
	//pthread_join(mthread,NULL);
	pthread_join(pthread,NULL);  // wait for the read thread to complete

	pthread_mutex_destroy(&mutex_fwrite);
	pthread_mutex_destroy(&mutex_gobjs);

	for (unsigned int i=0; i<g_objs.size(); i++) {
		delete (g_objs[i]);
	}
	delete g_daglx[0];
	delete g_daglx[1];
	delete g_tsc;

	return 0;
}
