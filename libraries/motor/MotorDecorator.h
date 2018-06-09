#pragma once

#include "motor.h"

class MotorDecorator : public Motor {

    Motor& motor;

public:
    MotorDecorator(Motor& motor) : motor(motor) {}

    MotorState getState() {
        return motor.getState();
    }

    //returns true in case of successfull operation
    bool setState(MotorState state) {
        return motor.setState(state);
    }

    //returns true in case of successfull operation
    bool setPower(byte power) {
        return motor.setPower(power);
    }

    char* getName() {
        return motor.getName();
    }
};