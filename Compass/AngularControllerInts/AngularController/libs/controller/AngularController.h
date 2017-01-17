// AngularController.h

#ifndef _ANGULARCONTROLLER_h
#define _ANGULARCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Abstract2WDController.h"
#include "libs\compass\compass.h"

#define DEFEFAULT_POSITION 0.0

float smoothAngle(int value);

enum TurnDirection
{
	NONE,
	LEFT,
	RIGHT
};

class AngularController : public Abstract2WDController
{
private:
	Compass* compass;
	TurnDirection turnDirection;
public:
	AngularController(Compass* compass);
	void startMotors();
	void reset();
	void turn(int angle);
	void turnTo(int newPos);
};

#endif

