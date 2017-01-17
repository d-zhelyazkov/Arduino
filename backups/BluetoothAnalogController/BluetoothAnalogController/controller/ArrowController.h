// ArrowController.h

#ifndef _ARROWCONTROLLER_h
#define _ARROWCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Abstract2WDController.h"

enum MoveDir
{
	UNDEF,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class ArrowController : public Abstract2WDController
{
public:
	MoveDir dir;

	ArrowController();
	void StartMotors();

};

#endif

