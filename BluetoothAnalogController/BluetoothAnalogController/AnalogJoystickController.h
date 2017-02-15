// AnalogJoystickController.h
#pragma once

#include "Motor.h"

class AnalogJoystickController
{
    Motor* mLeftMotor;
    Motor* mRightMotor;
public:
	AnalogJoystickController(Motor* left, Motor* right);


    //async
	void move(float x, float y);
	
    void stop();
};


