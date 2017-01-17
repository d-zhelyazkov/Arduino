#pragma once

#include "Arduino.h"
#include "Motor.h"

class MotorWithEncoder : public Motor {
	byte encoderPin;

public:
	MotorWithEncoder(byte directionPin, byte pwmPin, byte brakePin, byte encoderPin);
	
	void move(State direction, uint16_t encoderTicks);
};