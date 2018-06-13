#pragma once

#include "Observer.h"
#include "MotorDecorator.h"

//notifies observers when motor state is changed
class MotorObservable:
    public MotorDecorator,
    public Observable {

public:

    MotorObservable(Motor& motor) : MotorDecorator(motor) {}

    //returns true in case of successfull operation
    bool setState(MotorState state) {
        bool success = MotorDecorator::setState(state);

        if (!success)
            return false;

        notifyObservers();
        return true;
    }

    //returns true in case of successfull operation
    bool stop() {
        bool success = MotorDecorator::stop();

        if (!success)
            return false;

        notifyObservers();
        return true;
    }

};