// compass.h

#ifndef _COMPASS_h
#define _COMPASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Compass {

public:
	virtual float getDirectionInRadians() = 0;
	virtual float getDirectionInDegrees() = 0;
};

#endif

