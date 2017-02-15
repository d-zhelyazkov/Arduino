#pragma once
#include "Motor.h"
#include "PinInterruptCounter.h"

class MotorWithEncoder : public InterruptSystem::PinInterruptCounter {

    Motor* mMotor;
    bool mListening = false;
    uint16_t mStopTicks = 0;

    void interruptServiceRoutine();

public:
    MotorWithEncoder(Motor* motor, byte encoderPin);

    //async
    void move(MotorState direction, uint16_t encoderTicks);

    MotorState getState() {
        return mMotor->getState();
    }
};