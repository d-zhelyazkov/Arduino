// AnalogJoystickController.h

#ifndef _ANALOGJOYSTICKCONTROLLER_h
#define _ANALOGJOYSTICKCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Abstract2WDController.h"

class AnalogJoystickController : public Abstract2WDController
{
public:
	float x;
	float y;

	AnalogJoystickController();
	void StartMotors();
	bool VerifyParameters();
};

#endif

