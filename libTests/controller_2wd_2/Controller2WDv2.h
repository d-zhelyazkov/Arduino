#pragma once

#include "Arduino.h"
#include "MotorWithEncoder.h"
#include "compass.h"

enum ControllerState {STILL, MOOVING_FORWARD, MOOVING_BACKWARD, TURNING_LEFT, TURNING_RIGHT};

class Controller2WDv2 {
	MotorWithEncoder* leftMotor;
	MotorWithEncoder* rightMotor;
	Compass* compass;

public:
	Controller2WDv2(MotorWithEncoder* leftMotor, MotorWithEncoder* rightMotor, Compass* compass );

	void learn();

	//<0 to right
	//>0 to left
	// actual turn: +-180
	void turn(short degrees);

	void turn(uint16_t encoderTicks, ControllerState turnDir);

	//<0 forward
	//>0 backward
	void move(short ticks);

	ControllerState getState();

	bool isStopped();
};