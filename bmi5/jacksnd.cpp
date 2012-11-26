// this is adapted from jack's simple_client.c

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
#include "jacksnd.h"

jack_port_t *output_port1, *output_port2;
jack_client_t *client;

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

using namespace std; 

long g_jackSample; 

typedef struct
{
	float		sine[TABLE_SIZE+1];
	list<Tone*> tones; 
} paTestData;

static void signal_handler(int )
{
	jack_client_close(client);
	fprintf(stderr, "signal received, exiting ...\n");
	exit(0);
}

int process (jack_nframes_t nframes, void *arg)
{
	jack_default_audio_sample_t *out1, *out2;
	paTestData *data = (paTestData*)arg;

	out1 = (jack_default_audio_sample_t*)jack_port_get_buffer (output_port1, nframes);
	out2 = (jack_default_audio_sample_t*)jack_port_get_buffer (output_port2, nframes);

	for(unsigned int i=0; i<nframes; i++){
		out1[i] = 0.f; 
		out2[i] = 0.f; 
	}
	list<Tone*>::iterator it;
	for(it=data->tones.begin(); it != data->tones.end(); it++){
		for(unsigned int i=0; i<nframes && !((*it)->m_dead); i++){
			(*it)->sample(g_jackSample + i, &(out1[i]), &(out2[i]), data->sine); 
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
	g_jackSample += nframes; 
	return 0;      
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void jack_shutdown (void *){
	exit (1);
}

/* song stuff. well, not really a song -- more of a set of noises. */ 
float uniform(){ return ((float)rand() / (float)RAND_MAX);}
float uniformPan(){ return uniform()*2.f -1.f; }
void addTones(paTestData * data, long offset){
	float u = 0.f; float ui = 0.25; 
	float scl = offset / (SAMPFREQ*15); 
	if(scl > 1) scl = 1; 
	float scl2 = scl * 0.15; 
	scl += 0.1;
	float mel = 0.18f;
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
	t = new Tone(800.f, uniformPan(), mel*scl2*0.5, offset+u*SAMPFREQ, SAMPFREQ*1.3*scl); 
	data->tones.push_back(t); 
	t = new Tone(300.f, uniformPan(), mel*0.29, offset+u*SAMPFREQ, SAMPFREQ*scl); 
	data->tones.push_back(t);
	long bar = offset / (SAMPFREQ*3); 
	float distortion = (bar&15) - 4; 
	if(bar < 4) bar = 0;  
	float freqs[] = {150.f, 125.f, 100.f, 133.f}; 
	for(int i=0; i< 12; i++){
		t = new Tone(freqs[bar&3], 0.0, scl*(0.25+0.1*sin(i/2)), offset+((float)i*ui+ui/2)*SAMPFREQ, SAMPFREQ*ui*0.8); 
		t->m_distortion = distortion; 
		data->tones.push_back(t);
	}
	float freqs2[] = {112.5f, 93.75f, 75.f, 100.f}; 
	if((bar&31) > 15){
		for(int i=0; i< 12; i++){
			t = new Tone(freqs2[bar&3], 0.0, scl*(0.15+0.1*sin(i/2)), offset+((float)i*ui+ui)*SAMPFREQ, SAMPFREQ*ui*0.6); 
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
	t = new Tone(fb, uniformPan(), 0.3, offset+SAMPFREQ, SAMPFREQ*2); 
	t->m_attack = SAMPFREQ; 
	t->m_release = SAMPFREQ;
	t->m_distortion = 2 + bar/16; 
	data->tones.push_back(t);
}

static paTestData g_data;

int jackInit()
{
	const char **ports;
	const char *client_name;
	jack_status_t status;
	int i;

	for( i=0; i<TABLE_SIZE+1; i++ ){
		g_data.sine[i] = 0.2 * (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
	}
	g_jackSample = 0; 
	/* open a client connection to the JACK server */

	client = jack_client_open ("bmi5", JackNullOption, &status, NULL);
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

	jack_set_process_callback (client, process, &g_data);

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
		fprintf (stderr, "jack_activate cannot activate client");
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
		fprintf(stderr, "JACK: no physical playback ports\n");
		exit (1);
	}
	if (jack_connect (client, jack_port_name (output_port1), ports[0])) {
		fprintf (stderr, "JACK: cannot connect output ports\n");
	}
	if (jack_connect (client, jack_port_name (output_port2), ports[1])) {
		fprintf (stderr, "JACK: cannot connect output ports\n");
	}
	if (jack_connect (client, jack_port_name (output_port1), ports[4])) { //for my machine... 
		fprintf (stderr, "JACK: cannot connect output ports\n");
	}
	if (jack_connect (client, jack_port_name (output_port2), ports[5])) {
		fprintf (stderr, "JACK: cannot connect output ports\n");
	}
	free (ports);
	//make sure it's working ..
	addTones(&g_data, 0); 
	return 0; 
}
void jackDemo(){
	/* install a signal handler to properly quits jack client */
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);

	/* keep running until the Ctrl+C */
	addTones(&g_data, 0); 
	long offset = 0; 
	while (1) {
		sleep (3);
		offset += SAMPFREQ*3;
		addTones(&g_data, offset); 
	}
	jack_client_close (client);
	exit (0);
}
void jackAddTone(Tone* t){
	g_data.tones.push_back(t);
}
/*
int main(){
	jackInit(); 
	jackDemo(); 
	return 0; 
}
*/