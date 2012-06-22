// OptoFrame.c
#include "stdafx.h"

#include <math.h>


// LOCAL
#include "OptoServer.h"
#include "COptoServer.h"
#include "ComUtils.h"
#include "Matrix.h"


//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////
///////////////////////// TABLE ROTATION
/////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

// This routine calculates the rotation matrix to convert 
// from 3D to table positon coords.  Note that get3D returns positons 
// in cm's, and so these parameters are for use with CM data. 
//
// This section uses the homegrown "matrix" library       
//
// For Now, Assume that:
//
//      X is M1->M2
//      Y is M3 -> (X-axis)
//		Z is orthog to X,Y
//      orig is M1;

#define FRAME_MARKERS	3
#define FRAME_REPS		100
int
COptoServer::calcTableFrame()
{
	int n,i,j;
	matrix C(3,FRAME_MARKERS);
	matrix CX(FRAME_REPS,FRAME_MARKERS);
	matrix CY(FRAME_REPS,FRAME_MARKERS);
	matrix CZ(FRAME_REPS,FRAME_MARKERS);
	matrix ZERO(1,1);
	
	/*  Might use this if a 4th Marker Explicitly Marks Origin
	cout << "Position markers with fourth marker at Origin"
	MouseWait();
	*/


	// Collect Data
	put_active(1);
	for(n=0;n<FRAME_REPS;n++){
		OptoLatest(1);
		for(i=1;i<=FRAME_MARKERS;i++){
			CX(n+1,i) = pos[0][i-1];
			CY(n+1,i) = pos[1][i-1];
			CZ(n+1,i) = pos[2][i-1];
			for(j=1;j<=3;j++){
				C(j,i)+=(float)pos[j-1][i-1];
			}
		}

	}
	C/=(float)FRAME_REPS;

	put_active(0);
	// SoundTone(600,200);
	
	// CALCULATE THE ORTHOGONAL AXES in the RAW COORD FRAME
	matrix w,R,X,Y,Z,T;
	w=C[2]-C[1];									// X is from 1st to 2nd marker
	X=w/sqrt(scalar((~w)*w));
	w=(C[1]-C[3]) - X*((~X)*(C[1]-C[3]));			// Y is orthog, in plane of markers
	Y=w/sqrt(scalar((~w)*w));
	w=-C[1]+X*((~X)*C[1])+Y*((~Y)*C[1]);	// Z is orthog to XxY
	Z=w/sqrt(scalar((~w)*w));
	R=~(X|Y|Z);

	T = R*C[1];  // Origin M1

	// Put R into _Rot for data routines below
	rot= new float*[3];
	for(i=1;i<=3;i++){
		rot[i-1] = new float[4];
		for(j=1;j<=3;j++) rot[i-1][j-1]=(float)R(i,j);
		rot[i-1][3] = -T(i,1);
	}


	// OUTPUT
	write(C,"OptoFrame.txt");
	append(ZERO,"OptoFrame.txt");
	append(R,"OptoFrame.txt");
	append(ZERO,"OptoFrame.txt");
	append(T,"OptoFrame.txt");
	append(ZERO,"OptoFrame.txt");
	append(CX,"OptoFrame.txt");
	append(ZERO,"OptoFrame.txt");
	append(CY,"OptoFrame.txt");
	append(ZERO,"OptoFrame.txt");
	append(CZ,"OptoFrame.txt");

	return 0;
}

