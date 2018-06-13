#include "MotorWithEncoder.h"
#include "ExStream.h"

#define DEBUG(x)

bool MotorWithEncoder::move(MotorState direction, uint16_t encoderTicks)
{
    switch (direction)
    {
    case MotorState::ROT_CLOCK:
    case MotorState::ROT_ANTI_CLOCK:
        break;
    default:
        return false;
    }

    PinInterruptCounter::resetCounter();
    stopTicks = encoderTicks;
    InterruptSystem::attachInterrupt(this);

    bool successful = setState(direction);
    if (!successful) {
        InterruptSystem::deattachInterrupt(this);
        return false;
    }

    DEBUG(
    ExSerial.printf("%s started %s for %d ticks\n",
        getName(), motorStateToStr(direction), encoderTicks);
    )

    return true;
}

void MotorWithEncoder::interruptServiceRoutine()
{
    PinInterruptCounter::interruptServiceRoutine();
    uint16_t currentTicks = PinInterruptCounter::getValue();
    
    DEBUG(
    ExSerial.printf("%s - tick\n", getName());
    )

    if (currentTicks < stopTicks)
        return;

    InterruptSystem::deattachInterrupt(this);
    stop();

    DEBUG(
    ExSerial.printf("Stopped %s\n", getName());
    )
}
