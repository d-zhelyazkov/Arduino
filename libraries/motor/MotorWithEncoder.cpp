#include "MotorWithEncoder.h"

MotorWithEncoder::MotorWithEncoder(Motor* motor, byte encoderPin)
    : mMotor(motor), PinInterruptCounter(encoderPin) {
    attachInterrupt(this);
}

void MotorWithEncoder::move(MotorState direction, uint16_t encoderTicks)
{
    if (direction == MotorState::STOPPED)
        return;

    uint16_t currentTicks = PinInterruptCounter::getValue();
    mStopTicks = currentTicks + encoderTicks;
    if (mStopTicks <= currentTicks) {
        //uint16 overflow
        PinInterruptCounter::resetCounter();
        mStopTicks = encoderTicks;
    }

    mListening = true;
    mMotor->setState(direction);
}

void MotorWithEncoder::interruptServiceRoutine()
{
    PinInterruptCounter::interruptServiceRoutine();
    if (!mListening)
        return;

    if (mStopTicks < PinInterruptCounter::getValue())
        return;

    mMotor->setState(MotorState::STOPPED);
    mListening = false;
}
