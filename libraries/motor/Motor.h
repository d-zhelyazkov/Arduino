// Motor.h
#pragma once

#include "Arduino.h"

enum MotorState {STOPPED, ROT_CLOCK, ROT_ANTI_CLOCK };

class Motor
{
    MotorState mState = MotorState::STOPPED;
    
public:

    MotorState getState() { return mState; }

    //sets motor state
    //returns true in case of successfull operation
    virtual bool setState(MotorState state){
        mState = state;
        return true;
    }
};


