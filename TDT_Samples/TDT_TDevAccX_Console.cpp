// TDT_ActiveX_Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"

#import "C:\\TDT\\OpenEx\\OpenDev\\TDevAccX.ocx"

TDEVACCXLib::_DTDevAccXPtr TD;

int _tmain(int argc, _TCHAR* argv[])
{

	//Initialize ActiveX object
	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		printf("Failed to initialize COM!\n");
	}
	const char* appId = "{09EFA19D-3AD0-49A8-8232-18D6F7512CE8}"; //"TDevAccX.ocx"
	hr = TD.CreateInstance(appId);

	if (FAILED(hr)) {
		printf("CreateInstance for %s failed!\n", appId);
	}
	else {
		printf("Successfully initialized TDT ActiveX interface %s\n", appId);
	}

	if (0 == TD) return -1;
	//

	//TDT commands
	if (TD->ConnectServer("Local")) {
		printf("Connected to Workbench server\n");
	}

	int mode = TD->GetSysMode(); //0=Idle...3=Record
	printf("System Mode: %i\n",mode);

	float data[1000];
	float *p = data;

	int lastindex, currindex;
	
	lastindex = TD->GetTargetVal("RA16.sWave");  
	while(TD->GetSysMode()>1) { //loop while workbench is running
		Sleep(100);

		//read current index of 'Wave' store buffer on device 'RA16'
		currindex = TD->GetTargetVal("RA16.sWave");  
		printf("currindex %i \n",currindex);

		//read the new values of Ch1 of 'Wave' store buffer on device 'RA16' and assign it to data array
		TD->ReadTarget("RA16.dWave~1", lastindex, currindex, p);  
		
		//read 1000 points into 'data' array, starting at index '0'
		TD->ReadTarget("RA16.dWave~1", 0, 1000, p);  
		
		lastindex = currindex;
	}

	system("PAUSE");
	TD->CloseConnection();

	return 1;
}