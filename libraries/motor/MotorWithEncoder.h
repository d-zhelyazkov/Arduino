#pragma once

#include "Motor.h"
#include "PinInterruptCounter.h"
#include "MotorObserver.h"

class MotorWithEncoder :
    public InterruptSystem::PinInterruptCounter,
    public MotorObservable {

    uint16_t stopTicks = 0;

    void interruptServiceRoutine();

public:
    MotorWithEncoder(Motor* motor, byte encoderPin) :
        MotorObservable(*motor), PinInterruptCounter(encoderPin) {}

    //starts the motor
    //will asynchronously stop it after the specified encoder ticks
    //resets the interrupt counter
    //returns true if motor started successfully
    bool move(MotorState direction, uint16_t encoderTicks);

};