#include <math.h>

float bessy0(float x)
{
	float bessj0(float x);
	float z;
	double xx,y,ans,ans1,ans2;

	if (x < 8.0) {
		y=x*x;
		ans1 = -2957821389.0+y*(7062834065.0+y*(-512359803.6
			+y*(10879881.29+y*(-86327.92757+y*228.4622733))));
		ans2=40076544269.0+y*(745249964.8+y*(7189466.438
			+y*(47447.26470+y*(226.1030244+y*1.0))));
		ans=(ans1/ans2)+0.636619772*bessj0(x)*log(x);
	} else {
		z=8.0/x;
		y=z*z;
		xx=x-0.785398164;
		ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4
			+y*(-0.2073370639e-5+y*0.2093887211e-6)));
		ans2 = -0.1562499995e-1+y*(0.1430488765e-3
			+y*(-0.6911147651e-5+y*(0.7621095161e-6
			+y*(-0.934945152e-7))));
		ans=sqrt(0.636619772/x)*(sin(xx)*ans1+z*cos(xx)*ans2);
	}
	return ans;
}
/* (C) Copr. 1986-92 Numerical Recipes Software #.,. */
