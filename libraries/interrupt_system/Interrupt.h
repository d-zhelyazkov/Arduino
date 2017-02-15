#pragma once

#include "arduino.h"

namespace InterruptSystem {

    enum InterruptMode { ONCHANGE, ONRISING };

    class InterruptPort;

    class Interrupt {
        byte pin;
        InterruptMode mode = ONCHANGE;

    protected:
        virtual void interruptServiceRoutine() = 0;

        friend class InterruptPort;

    public:
        Interrupt(byte pin) : pin(pin) {}
        Interrupt(byte pin, InterruptMode mode) : pin(pin), mode(mode) {}

        byte getPin() { return pin; }
        InterruptMode getMode() { return mode; }


        ~Interrupt();
    };


    void printInterrupt(Interrupt* interrupt);

    void attachInterrupt(Interrupt* interrupt);
    void deattachInterrupt(Interrupt* interrupt);

};