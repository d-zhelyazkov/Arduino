#pragma once

#include "Interrupt.h"

namespace InterruptSystem {

    class PinInterruptCounter : public Interrupt
    {
        volatile uint16_t mCounter = 0;

    protected:
        virtual void interruptServiceRoutine() {
            mCounter++;
        }

    public:
        using Interrupt::Interrupt;


        uint16_t getValue() {
            return mCounter;
        }

        void resetCounter() {
            mCounter = 0;
        }
    };

};

