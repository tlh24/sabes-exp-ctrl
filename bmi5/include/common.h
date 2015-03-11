#ifndef _COMMON_
#define _COMMON_

union floatbytes {
	float f;
	unsigned int u;
	char b[sizeof(float)];
};


#endif
