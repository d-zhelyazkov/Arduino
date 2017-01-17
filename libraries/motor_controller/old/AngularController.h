// AngularController.h

#ifndef _ANGULARCONTROLLER_h
#define _ANGULARCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Abstract2WDController.h"
#include "compass.h"

#define DEFEFAULT_POSITION 0.0

class AngularController : public Abstract2WDController
{
private:
	Compass* compass;
public:
	AngularController(Compass* compass);
	void reset();
	void turn(float angle);
	void turnTo(float newPos);
};

#endif

