// compass.h

#ifndef _COMPASS_h
#define _COMPASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#define PI_DEG 180
#define PI_DEGx2 360

class Compass {

public:
	//[-PI;PI]
	virtual float getDirectionInRadians() = 0;

	//[0;360]
	virtual float getDirectionInDegrees();
};

#endif

