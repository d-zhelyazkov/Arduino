// Abstract2WDController.h

#ifndef _ABSTRACT2WDCONTROLLER_h
#define _ABSTRACT2WDCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Motor.h"
#include "AbstractInterruptor.h"

#define B_DIR 13
#define B_PWM 11
#define B_BRK 8
#define A_DIR 12
#define A_PWM 3
#define A_BRK 9
#define MAX_POWER 255
#define MIN_POWER 100


enum SteerDirection
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const char* getSteerDirectionStr(const SteerDirection diretion);

class Abstract2WDController
{
private:
	AbstractInterruptor* interruptor;

protected:
	const Motor* bMotor;
	const Motor* aMotor;

	SteerDirection steerDirection;

	Abstract2WDController();

public:
	void move();
	void stop();
	void setInterruptor(AbstractInterruptor*);
};

#endif

