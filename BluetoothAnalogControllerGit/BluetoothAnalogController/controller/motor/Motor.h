// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


class Motor
{
	unsigned short directionPin;
	unsigned short pwmPin;
	unsigned short brakePin;

public:
	Motor(unsigned short directionPin, unsigned short pwmPin, unsigned short brakePin);
	void Move(bool direction);
	void Stop();
	void SetPower(unsigned short power);
};

#endif

