// TestController.h

#ifndef _TESTCONTROLLER_h
#define _TESTCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Abstract2WDController.h"

class TestController : public Abstract2WDController
{
public:
	TestController();
	void StartMotors();
};

#endif

