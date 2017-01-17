// ArrowController.h

#ifndef _ARROWCONTROLLER_h
#define _ARROWCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Abstract2WDController.h"

#define MOVE_DIR_CNT 5

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

