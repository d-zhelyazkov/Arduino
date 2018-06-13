#include "Motor.h"

char* motorStateToStr(MotorState state) {
    switch (state)
    {
    case STOPPED:
        return "STOP";
    case ROT_CLOCK:
        return "ROT_CLOCK";
    case ROT_ANTI_CLOCK:
        return "ROT_A_CLOCK";
    default:
        return "N/A";
    }
}