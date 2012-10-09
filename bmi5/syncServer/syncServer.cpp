#include "stdafx.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "float.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27707"

#import "C:\\TDT\\ActiveX\\RPcoX.ocx"

RPCOXLib::_DRPcoXPtr RP;

double PCFreq = 0.0;
__int64 CounterStart = 0;
__int64 CounterLast = 0; 
bool	g_die = false; 
double g_offset = 0; // ticks = perf.ctr * slope + offset.
double g_slope = 24.414065; 

void StartCounter()
{
    __int64 li;
    if(!QueryPerformanceFrequency((LARGE_INTEGER*)&li))
        printf("QueryPerformanceFrequency failed!\n");

    PCFreq = double(li)/1000.0; //puts the time in msec.

    QueryPerformanceCounter((LARGE_INTEGER*)&CounterStart);
}
double GetCounter()
{
    __int64 li;
    QueryPerformanceCounter((LARGE_INTEGER*)&li);
	CounterLast = li; 
    return double(li-CounterStart)/PCFreq;
}

DWORD WINAPI syncThread( LPVOID lpParam ) {
    WSADATA wsaData;
    int iResult;

    SOCKET sd = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sd == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the UDP listening socket
    iResult = bind( sd, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(sd);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

	/* Loop and get data from clients */
	while (!g_die){
		int client_length = (int)sizeof(struct sockaddr_in);
		struct sockaddr_in client;
		/* Receive bytes from client */
		int n = recvfrom(sd, recvbuf, recvbuflen, 0, (struct sockaddr *)&client, &client_length);
		double recvtime = GetCounter()/1000.0; //communication in seconds.
		if (n < 0 || (n % 8)){
			fprintf(stderr, "Could not receive datagram.\n");
			closesocket(sd);
			WSACleanup();
			return 0; 
		}
		double *senttime = (double*)recvbuf; 
		//linux will send it's time; we return with out estimate of skew + delay.
		double skew_delay = recvtime - *senttime; 
		double sendbuf[4]; 
		//reply with our time,  skew + delay estimate, offset, and slope.
		int len = 32; 
		sendbuf[1] = skew_delay;
		sendbuf[2] = g_offset; 
		sendbuf[3] = g_slope; 
		sendbuf[0] = GetCounter()/1000.0; 
		if (sendto(sd, (char*)sendbuf, len, 0, (struct sockaddr *)&client, client_length) != len){
			fprintf(stderr, "Error sending datagram.\n");
			closesocket(sd);
			WSACleanup();
			return 0; 
		}
	}
	closesocket(sd);
	WSACleanup();
    return 0;
}

DWORD WINAPI tdtThread( LPVOID lpParam ) {
	int n = 2000000; 
	double* data = (double*)malloc(n*8*4); 
	double preval = 0; 
	StartCounter(); 
	// next task: iteratively estimate both the offset and slope for converting the performance counter to 
	// tdt ticks. 
	double updaterate = 0.0005; //update the offset. increase this if the sign of the update is consistently one sign.
	double lastupdate = 0; 
	double fabsupdate = 1.0; 
	int rejected = 0; 
	int i = 0; 
	while(!g_die){
		double pt = GetCounter(); //pre-time: estimate how long the call took. 
		unsigned int itime = (unsigned int)floor(RP->GetTagVal("TimeTicks"));
		double dt = GetCounter(); 
		unsigned int itime2 = (unsigned int)floor(RP->GetTagVal("TimeTicks2")); 
		// itime is assumed to be accurate; however, itime2 may have wrapped between calls.
		// eg. if the shift is 12, actual time = 4090, itime = 4090, itime2 = 1. 
		// this would cause a blip of +4096.  bad!
		// if we duplicate bit 11 in both calls, then we can detect a wrap. 
		// as above, now itime2 = 2 (10); itime says that bit 0 should be 1, 
		// so will need to subtract itime bit 11 from itime2, then mask. 
		// in practice, we are using base 16 for communication.
		itime2 <<= 15; 
		unsigned int wrap = (itime2 ^ itime) & (1 << 15); 
		if(wrap) itime2 -= (1 << 15); 
		itime2 &= 0xffff0000; 
		double ticks = (double)itime + (double)itime2; 
		double pred = dt * g_slope + g_offset; //ticks = dt * slope + offset (estimated)
		double update = ticks - pred; //will ultimately need to do outlier rejection here, once things are settled.
		if(i<n){
			data[i*4+0] = g_slope ;
			data[i*4+1] = g_offset / 24.414; 
			data[i*4+2] = update / 24.414; //in ms.
			data[i*4+3] = updaterate; //call time.  see if the call time predicts the update -- if the call time was long (RZ2 took a while to get back to us), 
		}// then the predicted count will be larger than the actual count, and the update will be negative. 
		// one alternative is to average pt and dt when predicting the RZ2 ticks. 
		// testing with matlab indicates that it is best to query the performance counter *after* GetTagVal.
		if(g_offset == 0.0) g_offset = ticks - dt * g_slope; //start condition.
		else {
			//delay is +- 0.5ms -> 12 samples. seems like a lot?
			g_offset += update * updaterate;
			g_slope += update * updaterate * 0.013969408716095; //lovely stochastic filters.
			if(fabsupdate > 0.0){
				if(fabs(lastupdate)/fabsupdate > 0.1) updaterate += 2.18610584286e-5; //same sign, update rate should be increased.
				else updaterate -= 1.28350384521e-5; //why these random numbers?  to prevent closed cycles in the FPU. 
				// bit-resonace which causes biased offset and slope estimates.  discovered empirically. 
			}
			if(updaterate > 0.09) updaterate = 0.09; 
			updaterate = fabs(updaterate); 
			lastupdate = 0.9* lastupdate + 0.1 * update; 
			fabsupdate = 0.9* fabsupdate + 0.1 * fabs(update); 
		}
		if((i%10000) == 0)
		printf("slope %f offset %f update %f call %f rate %f\n", g_slope, g_offset, update/g_slope, dt-pt, updaterate); 
		//periodically we'll need to update dt to avoid running out of 'double' bits. 
		//if(dt > 2000.0){
		//	g_offset = dt * g_slope + g_offset; //dt will be set to zero, below.
		//	CounterStart = CounterLast; 
		//}
		i++; 
	}
	FILE* fid; 
	if(fopen_s(&fid, "timing.txt", "w") == 0){
		for(int i=0; i<n; i++){
			fprintf(fid, "%f %f %f %f\n", data[i*4], data[i*4+1], data[i*4+2], data[i*4+3]); 
		}
		fclose(fid); 
	}
	free(data); 
	printf("rejected %d samples of %d (%f)\n", rejected, n, (double)rejected/(double)n); 
	return NULL; 
}

int _tmain(int argc, _TCHAR* argv[])
{
	// switch to 80-bit double FPU resolution. 
	unsigned int prevFpuState; 
	_controlfp_s(&prevFpuState, _PC_64, MCW_PC); 
	printf("sizeof(double) %d\n,", sizeof(double)); 

	const char* circuitPath = "C:\\Profiles\\tlh24\\JEO_Code\\TDT_Projects\\joeyos_baseline_project\\RCOCircuits\\Timing_Rec_Bin_RZ2_1.rcx"; 
	//const char* circuitPath = "C:\\TDT\\ActiveX\\ActXExamples\\RP_files\\Band_Limited_Noise.rcx";

	//Initialize ActiveX object
	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		printf("Failed to initialize COM!\n");
	}
	const char* appId = "{d323a625-1d13-11d4-8858-444553540000}"; //"RPcoX.ocx"
	hr = RP.CreateInstance(appId);

	if (FAILED(hr)) {
		printf("CreateInstance for %s failed!\n", appId);
	}
	else {
		printf("Successfully initialized TDT ActiveX interface %s\n", appId);
	}

	if (0 == RP) return -1;
	//TDT ActiveX commands
	if (RP->ConnectRZ2("GB",1)) {  
		printf("Connected to RZ2\n");
	}
	if (!RP->ClearCOF()) {  
		printf("ClearCOF failed\n");
	}
	if (RP->LoadCOF(circuitPath)) {
		printf("%s Loaded\n", circuitPath);
	}
	if (RP->Run()) {  
		printf("Circuit running\n");
	}
	StartCounter(); 
	bool monotonic = true;
	double oldtime = 0.0; 
	double var = 0.0; 
	for(int i=0; i<2000; i++){
		unsigned int itime = (unsigned int)floor(RP->GetTagVal("TimeTicks"));
		unsigned int itime2 = (unsigned int)floor(RP->GetTagVal("TimeTicks2")); 
		itime2 <<= 15; 
		unsigned int wrap = (itime2 ^ itime) & (1 << 15); 
		if(wrap) itime2 -= (1 << 15); 
		itime2 &= 0xffff0000; 
		double ticks = (double)itime + (double)itime2; 
		if(ticks < oldtime) monotonic = false; 
		var += (oldtime - ticks)*(oldtime - ticks)/24.414; // convert samples to ms. 
		oldtime = ticks; 
		//printf("sample count: %f\n", realtime); 
	}
	var /= 2; // now convert to us.
	var = sqrt(var); 
	double dt = GetCounter(); 
	printf("average time to query RZ2 tick count: %f us\n std of intercall time: %f us\n", dt/2.0, var); 
	if(!monotonic) printf("NOT monotonic!\n"); 
	monotonic = true; oldtime = 0.0; var = 0.0; 
	StartCounter(); 
	for(int i=0; i<2000; i++){
		dt = GetCounter(); 
		if(dt < oldtime) monotonic = false; 
		var += (oldtime - dt)*(oldtime - dt); 
		oldtime = dt; 
	}
	var /= 2; // in us.
	var = sqrt(var); 
	printf("average time to query performance counter: %f us\n std of intercall time %f us\n", dt/2.0, var); 
	if(!monotonic) printf("NOT monotonic!\n"); 

	//start up the sync thread -- 
	DWORD id = 1; 
	HANDLE synct = CreateThread( NULL,  0, syncThread, 0, 0, &id); 
	//start up the tdt thread -- 
	HANDLE tdtt = CreateThread( NULL,  0, tdtThread, 0, 0, &id); 

	
	printf("Press Enter to halt circuit and exit");
	getchar();
	g_die = true; 

	RP->Halt();

	//restore FPU state. 
	_controlfp_s(NULL, prevFpuState, MCW_PC); 
	//wait for the sync thread.
	WaitForSingleObject(synct, 2000); 
	return 0;
}

void vextest(){
	//VARIANT v = RP->ReadTagV("TimeTicks", 0, 1); //the same as below.
	HRESULT hr; 
	VARIANT v = RP->ReadTagVEX("TimeTicks", 0, 1, "I32", "F64", 1);
	SAFEARRAY* parray = v.parray; //access the VARIANT union.
	if( v.vt != (VT_ARRAY | VT_R8) ){ //this is probably correct -- we request a double and get one in an array.
		printf("wrong variant type! not 8 byte float!\n"); 
	}
	VARTYPE tSaType; 
	SafeArrayGetVartype(parray, &tSaType); 
	if(tSaType != VT_RECORD ){ //why is this a record?  and how do we unbox this? 
		printf("wrong safearray type -- not a VT_RECORD (??)\n"); 
	}
	int ndims = SafeArrayGetDim(parray); 
	printf("SafeArrayGetDim %d\n", ndims); //total junk: 65k
	unsigned int* iarray; 
	hr = SafeArrayAccessData(parray, (void**)&iarray); //passes, but iarray = NULL, consistent with VT_RECORD.
	if(FAILED(hr))
		printf("SafeArrayAccessData failed! \n"); 
	unsigned int itime2 = iarray[0]; 
	printf("time %f\n", itime2); 

	hr = SafeArrayUnaccessData(parray); 
}
