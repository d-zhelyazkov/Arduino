// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

enum MoveDirection { FORWARD, BACKWARD };

class Motor
{
	unsigned short directionPin;
	unsigned short pwmPin;
	unsigned short brakePin;

public:
	Motor(unsigned short directionPin, unsigned short pwmPin, unsigned short brakePin);
	void Move(MoveDirection direction) const;
	void Stop() const;
	void SetPower(unsigned short power) const;
};

#endif

