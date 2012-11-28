/** @file simple_client.c
 *
 * @brief This simple client demonstrates the basic features of JACK
 * as they would be used by many applications.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <jack/jack.h>
#include <list>

jack_port_t *output_port1, *output_port2;
jack_client_t *client;

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define TABLE_SIZE   (200)
#define SAMPFREQ		48000.0

using namespace std; 

class Tone{
public:
	float		m_s1; 
	float		m_s2; 
	double	m_phase; 
	double	m_pincr; 
	double	m_poff; 
	long		m_start; //in samples
	long		m_duration; // in samples; 
	long		m_attack; 
	long		m_release; 
	float		m_distortion; 
	bool		m_dead; 
	
	Tone(float freq, float pan, float scale, long start, long duration){
		m_s1 = 1.f - pan; 
		m_s2 = pan + 1;
		if(m_s1 > 1.f) m_s1 = 1.f; 
		if(m_s2 > 1.f) m_s2 = 1.f; 
		m_s1 *= scale; 
		m_s2 *= scale; 
		m_phase = 0.0; 
		m_pincr = (double)freq / SAMPFREQ; 
		m_dead = false; 
		m_start = start; 
		m_duration = duration; 
		m_attack = 1000; 
		m_release = 1000; 
		m_distortion = 0.f; 
		m_poff = 0.0;
	}
	~Tone(){}
	
	void sample(long s, float* d1, float* d2, float* sine){
		if(m_dead || s > m_start + m_duration + m_release){
			m_dead = true; 
		} else {
			if(m_start == -1) m_start = s; 
			if(m_start <= s){
				float env = 1.f;
				if(s-m_start < m_attack)
					env = (float)(s-m_start) / (float)m_attack; 
				else if(s-m_start >= m_duration)
					env = 1.f - (float)(s-m_start-m_duration) / (float)m_release; 
				env < 0.f ? 0.f : env; 
				env > 1.f ? 1.f : env; 
				double phase = m_phase * TABLE_SIZE; 
				int bot = (int)floor(phase); 
				if(bot > TABLE_SIZE-1) bot = TABLE_SIZE-1; 
				int top = bot+1; 
				double lerp = phase - floor(phase); 
				float a = (1-lerp)*sine[bot] + lerp*sine[top]; 
				if(m_distortion > 0.f)
					a = atan(a * (1 + m_distortion)) / atan(1+m_distortion); 
				*d1 += a * m_s1 * env; 
				*d2 += a * m_s2 * env; 
				m_phase += m_pincr; 
				if(m_phase > 1.0) m_phase -= 1.0; 
			}
		}
	}
};

typedef struct
{
	long		sample; //total number of samples. 
	float		sine[TABLE_SIZE+1];
	list<Tone*> tones; 
} paTestData;

static void signal_handler(int sig)
{
	jack_client_close(client);
	fprintf(stderr, "signal received, exiting ...\n");
	exit(0);
}

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client follows a simple rule: when the JACK transport is
 * running, copy the input port to the output.  When it stops, exit.
 */

int process (jack_nframes_t nframes, void *arg)
{
	jack_default_audio_sample_t *out1, *out2;
	paTestData *data = (paTestData*)arg;
	int i;

	out1 = (jack_default_audio_sample_t*)jack_port_get_buffer (output_port1, nframes);
	out2 = (jack_default_audio_sample_t*)jack_port_get_buffer (output_port2, nframes);

	for( i=0; i<nframes; i++){
		out1[i] = 0.f; 
		out2[i] = 0.f; 
	}
	list<Tone*>::iterator it;
	for(it=data->tones.begin(); it != data->tones.end(); it++){
		for(int i=0; i<nframes && !((*it)->m_dead); i++){
			(*it)->sample(data->sample + i, &(out1[i]), &(out2[i]), data->sine); 
		}
	}
	//remove the 'dead' tones. 
	it = data->tones.begin(); 
	while(it != data->tones.end()){
		if((*it)->m_dead){
			Tone* t = (*it); 
			it = data->tones.erase(it); 
			delete t; 
		} else {
			it++; 
		}
	}
	data->sample += nframes; 
	return 0;      
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void
jack_shutdown (void *arg)
{
	exit (1);
}
float uniform(){ return ((float)rand() / (float)RAND_MAX);}
float uniformPan(){ return uniform()*2.f -1.f; }

void addTones(paTestData * data, long offset){
	float u = 0.f; float ui = 0.25; 
	float scl = offset / (SAMPFREQ*3*4); 
	if(scl > 1) scl = 1; 
	float scl2 = scl * 0.15; 
	float mel = 0.165f;
	long bar = offset / (SAMPFREQ*3); 
	Tone* t; 
	t = new Tone(500.f, uniformPan(), mel*0.25, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui; 
	t = new Tone(600.f, uniformPan(), mel*0.15, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui; 
	t = new Tone(750.f, uniformPan(), mel*0.23, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui; 
	t = new Tone(300.f, uniformPan(), mel*0.2, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui; 
	t = new Tone(400.f, uniformPan(), mel*0.22, offset+u*SAMPFREQ, SAMPFREQ*1.3*scl); 
	data->tones.push_back(t); u += ui; 
	if(bar&1 == 0)
		t = new Tone(700.f, uniformPan(), mel*scl2*0.5, offset+u*SAMPFREQ, SAMPFREQ*1.3*scl); 
	else
		t = new Tone(800.f, uniformPan(), mel*scl2*0.5, offset+u*SAMPFREQ, SAMPFREQ*1.3*scl); 
	data->tones.push_back(t); 
	t = new Tone(300.f, uniformPan(), mel*0.29, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t);
	float distortion = (bar&15) - 4; 
	if(bar < 4) bar = 0;  
	float freqs[] = {150.f, 125.f, 100.f, 133.f}; 
	for(int i=0; i< 12; i++){
		t = new Tone(freqs[bar&3], 0.0, scl*(0.22+0.08*sin(i/2)), offset+((float)i*ui+ui/2)*SAMPFREQ, SAMPFREQ*ui*0.8); 
		t->m_distortion = distortion; 
		data->tones.push_back(t);
	}
	float freqs2[] = {112.5f, 93.75f, 75.f, 100.f}; 
	if(bar&31 > 15){
		for(int i=0; i< 12; i++){
			t = new Tone(freqs2[bar&3], 0.0, scl*(0.12+0.06*sin(i/2)), offset+((float)i*ui+ui)*SAMPFREQ, SAMPFREQ*ui*0.6); 
			t->m_distortion = distortion; 
			data->tones.push_back(t);
		}
		for(int i=0; i<6; i++){
			t = new Tone(9000, 0.0, scl*(0.02+0.01*cos(i)), offset+((float)i*ui*2+ui)*SAMPFREQ, SAMPFREQ*ui*0.05); 
			t->m_attack = 200; 
			t->m_release = 2500; 
			data->tones.push_back(t);
		}
	}
	for(int i=0; i<6; i++){
		t = new Tone(8000, 0.0, scl*(0.04+0.02*cos(i)), offset+((float)i*ui*2)*SAMPFREQ, SAMPFREQ*ui*0.05); 
		t->m_attack = 200; 
		t->m_release = 2500; 
		data->tones.push_back(t);
	}
	t = new Tone(8000, 0.0, scl*(0.03), offset+((float)2*ui*2+ui/2)*SAMPFREQ, SAMPFREQ*ui*0.08); 
	t->m_attack = 200; 
	t->m_release = 2500; 
	data->tones.push_back(t);
		t = new Tone(8000, 0.0, scl*(0.03), offset+((float)5*ui*2+ui/2)*SAMPFREQ, SAMPFREQ*ui*0.08); 
	t->m_attack = 200; 
	t->m_release = 2500; 
	data->tones.push_back(t);
	float fb = 50.f; 
	if(bar & 1) fb = 66.f; 
	t = new Tone(fb, uniformPan(), 0.2, offset+SAMPFREQ, SAMPFREQ*2); 
	t->m_attack = SAMPFREQ; 
	t->m_release = SAMPFREQ;
	t->m_distortion = 2 + bar/16; 
	data->tones.push_back(t);
}

void addTones2(paTestData * data, long bar){
	float u = 0.f; float ui = 0.25; 
	float scl = 1.f; 
	float freq = 
	t = new Tone(300.f, 0.0, mel*0.2, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui; 
	t = new Tone(400.f, 0.0, mel*0.2, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui;
	t = new Tone(500.f, 0.0, mel*0.2, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t); u += ui;
}

int main (int argc, char *argv[])
{
	const char **ports;
	const char *client_name;
	const char *server_name = NULL;
	jack_options_t options = JackNullOption;
	jack_status_t status;
	paTestData data;
	int i;

	if (argc >= 2) {		/* client name specified? */
		client_name = argv[1];
		if (argc >= 3) {	/* server name specified? */
			server_name = argv[2];
            int my_option = JackNullOption | JackServerName;
			options = (jack_options_t)my_option;
		}
	} else {			/* use basename of argv[0] */
		client_name = strrchr(argv[0], '/');
		if (client_name == 0) {
			client_name = argv[0];
		} else {
			client_name++;
		}
	}

	for( i=0; i<TABLE_SIZE+1; i++ ){
		data.sine[i] = 0.2 * (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
	}
	data.sample = 0; 
	addTones(&data, 0); 
	/* open a client connection to the JACK server */

	client = jack_client_open (client_name, options, &status, server_name);
	if (client == NULL) {
		fprintf (stderr, "jack_client_open() failed, "
			 "status = 0x%2.0x\n", status);
		if (status & JackServerFailed) {
			fprintf (stderr, "Unable to connect to JACK server\n");
		}
		exit (1);
	}
	if (status & JackServerStarted) {
		fprintf (stderr, "JACK server started\n");
	}
	if (status & JackNameNotUnique) {
		client_name = jack_get_client_name(client);
		fprintf (stderr, "unique name `%s' assigned\n", client_name);
	}
	/* tell the JACK server to call `process()' whenever
	   there is work to be done.
	*/

	jack_set_process_callback (client, process, &data);

	/* tell the JACK server to call `jack_shutdown()' if
	   it ever shuts down, either entirely, or if it
	   just decides to stop calling us.
	*/

	jack_on_shutdown (client, jack_shutdown, 0);

	/* create two ports */

	output_port1 = jack_port_register (client, "output1",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput, 0);

	output_port2 = jack_port_register (client, "output2",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput, 0);

	if ((output_port1 == NULL) || (output_port2 == NULL)) {
		fprintf(stderr, "no more JACK ports available\n");
		exit (1);
	}

	/* Tell the JACK server that we are ready to roll.  Our
	 * process() callback will start running now. */

	if (jack_activate (client)) {
		fprintf (stderr, "cannot activate client");
		exit (1);
	}

	/* Connect the ports.  You can't do this before the client is
	 * activated, because we can't make connections to clients
	 * that aren't running.  Note the confusing (but necessary)
	 * orientation of the driver backend ports: playback ports are
	 * "input" to the backend, and capture ports are "output" from
	 * it.
	 */
 	
	ports = jack_get_ports (client, NULL, NULL,
				JackPortIsPhysical|JackPortIsInput);
	if (ports == NULL) {
		fprintf(stderr, "no physical playback ports\n");
		exit (1);
	}

	if (jack_connect (client, jack_port_name (output_port1), ports[0])) {
		fprintf (stderr, "cannot connect output ports\n");
	}

	if (jack_connect (client, jack_port_name (output_port2), ports[1])) {
		fprintf (stderr, "cannot connect output ports\n");
	}
	
	if (jack_connect (client, jack_port_name (output_port1), ports[4])) { //for my machine... 
		fprintf (stderr, "cannot connect output ports\n");
	}

	if (jack_connect (client, jack_port_name (output_port2), ports[5])) {
		fprintf (stderr, "cannot connect output ports\n");
	}

	free (ports);
    
    /* install a signal handler to properly quits jack client */
#ifdef WIN32
	signal(SIGINT, signal_handler);
    signal(SIGABRT, signal_handler);
	signal(SIGTERM, signal_handler);
#else
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
#endif

	/* keep running until the Ctrl+C */
	long offset = 0; 
	while (1) {
	#ifdef WIN32 
		Sleep(1000);
	#else
		sleep (3);
		offset += SAMPFREQ*3;
		addTones(&data, offset); 
	#endif
	}

	jack_client_close (client);
	exit (0);
}
