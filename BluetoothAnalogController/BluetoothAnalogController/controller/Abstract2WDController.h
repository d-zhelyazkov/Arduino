// Abstract2WDController.h

#ifndef _ABSTRACT2WDCONTROLLER_h
#define _ABSTRACT2WDCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "motor/Motor.h"
#include "../interruptor/AbstractInterruptor.h"

#define B_DIR 13
#define B_PWM 11
#define B_BRK 8
#define A_DIR 12
#define A_PWM 3
#define A_BRK 9
#define MAX_POWER 255

class Abstract2WDController
{
protected:
	Motor leftMotor;
	Motor rightMotor;
	virtual void StartMotors() = 0;

public:
	AbstractInterruptor *interruptor;
	Abstract2WDController();
	void Move();
	void Stop();
};

#endif

