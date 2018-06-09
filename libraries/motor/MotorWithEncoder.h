#pragma once
#include "Motor.h"
#include "PinInterruptCounter.h"
#include "MotorDecorator.h"

class MotorWithEncoder :
    public InterruptSystem::PinInterruptCounter,
    public MotorDecorator {

    volatile bool mListening = false;
    uint16_t mStopTicks = 0;

    void interruptServiceRoutine();

public:
    MotorWithEncoder(Motor* motor, byte encoderPin);

    //async
    void move(MotorState direction, uint16_t encoderTicks);

};