// Motor.h
#pragma once

#include "Arduino.h"

enum MotorState {STOPPED, ROT_CLOCK, ROT_ANTI_CLOCK };

class Motor
{    
public:

    virtual MotorState getState() = 0;

    //returns true in case of successfull operation
    virtual bool setState(MotorState state) = 0;

    //returns true in case of successfull operation
    virtual bool setPower(byte power) = 0;
};


