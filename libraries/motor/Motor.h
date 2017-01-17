// Motor.h
#pragma once

#include "Arduino.h"

enum State {STOPPED, ROT_CLOCK, ROT_ANTI_CLOCK };

class Motor
{
	byte directionPin;
	byte pwmPin;
	byte brakePin;
	State state = State::STOPPED;

public:
	Motor(byte directionPin, byte pwmPin, byte brakePin);
	void move(State direction);
	void stop();
	void setPower(byte power);
	State getState();
};


