// compass.h
#pragma once

#include "Arduino.h"

#define PI_DEG 180
#define PI_DEGx2 360

class Compass {

public:
	//[-PI;PI]
	virtual float getDirectionInRadians() = 0;

	//[0;360]
	virtual float getDirectionInDegrees();
};