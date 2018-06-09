#include "Motor.h"

char* motorStateToStr(MotorState state) {
    switch (state)
    {
    case STOPPED:
        return "STOPPED";
    case ROT_CLOCK:
        return "ROTATING CLOCKWISE";
    case ROT_ANTI_CLOCK:
        return "ROTATING ANTI CLOCKWISE";
    default:
        return "UNKNOWN";
    }
}