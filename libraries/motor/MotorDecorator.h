#pragma once

#include "Motor.h"

class MotorDecorator : public Motor {

    Motor& motor;

public:
    MotorDecorator(Motor& motor) : motor(motor) {}

    virtual MotorState getState() {
        return motor.getState();
    }

    //returns true in case of successfull operation
    virtual bool setState(MotorState state) {
        return motor.setState(state);
    }

    //returns true in case of successfull operation
    virtual bool stop() {
        return motor.stop();
    }

    //returns true in case of successfull operation
    virtual bool setPower(byte power) {
        return motor.setPower(power);
    }

    virtual char* getName() {
        return motor.getName();
    }
};