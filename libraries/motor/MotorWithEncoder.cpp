#include "MotorWithEncoder.h"

MotorWithEncoder::MotorWithEncoder(Motor* motor, byte encoderPin)
    : PinInterruptCounter(encoderPin), MotorDecorator(*motor) {

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

    Serial.print("Starting "); Serial.print(getName());
    Serial.print(" New state: "); Serial.print(motorStateToStr(direction));
    Serial.print(" Ticks: "); Serial.print(PinInterruptCounter::getValue());
    Serial.print(" - "); Serial.println(mStopTicks);

    mListening = true;
    setState(direction);
}

void MotorWithEncoder::interruptServiceRoutine()
{
    PinInterruptCounter::interruptServiceRoutine();
    uint16_t currentTicks = PinInterruptCounter::getValue();
    //Serial.print("Tick received: "); Serial.print(getName());
    //Serial.print("; Ticks: "); Serial.print(currentTicks);
    //Serial.print(" - "); Serial.println(mStopTicks);

    if (!mListening)
        return;

    if (currentTicks < mStopTicks)
        return;

    mListening = false;
    setState(MotorState::STOPPED);

    Serial.print("Stopped "); Serial.print(getName());
    Serial.print("; Ticks: "); Serial.print(currentTicks);
    Serial.print(" - "); Serial.println(mStopTicks);
}
