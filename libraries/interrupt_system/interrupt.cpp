#include "Interrupt.h"

using namespace InterruptSystem;

#define PINS_PER_PORT 8

namespace InterruptSystem {

    class InterruptPort {
        volatile byte mLastPortState = 0;
        Interrupt* mInterrupts[PINS_PER_PORT] = { 0 };

    public:
        //returns true on success
        //false - if there is already attached interrupt on that pin
        bool attachInterrupt(Interrupt* interrupt);

        void deattachInterrupt(Interrupt* interrupt);

        void interruptOccured(byte portState);

        bool hasEnabledPins();
    };


    InterruptPort* ATMEGA_328_INT_PORTS[3] = { 0 };		//ports B(0), C(1), D(2)


    void attachInterrupt(Interrupt * interrupt)
    {
        byte pin = interrupt->getPin();

        byte portNum = digitalPinToPCICRbit(pin);
        InterruptPort* port = ATMEGA_328_INT_PORTS[portNum];
        if (!port) {
            //Serial.printf("Enabling interrupt port %hhu.\n", portNum);
            port = ATMEGA_328_INT_PORTS[portNum] = new InterruptPort();
            byte portNumBinary = bit(portNum);
            PCIFR |= portNumBinary; // clear any outstanding interrupt
            PCICR |= portNumBinary; // enable interrupts for the port 
        }

        //Serial.printf("Attaching interrupt on pin %hhu to port %hhu\n", pin, portNum);
        port->attachInterrupt(interrupt);
    }

    void deattachInterrupt(Interrupt * interrupt)
    {
        byte pin = interrupt->getPin();
        byte portNum = digitalPinToPCICRbit(pin);
        InterruptPort* port = ATMEGA_328_INT_PORTS[portNum];
        if (!port)
            return;

        //Serial.print("Deattaching interrupt pin "); Serial.print(pin); Serial.print(" from port "); Serial.println(portNum);
        port->deattachInterrupt(interrupt);
        //Serial.println("Done disabling pin.");

        if (port->hasEnabledPins())
            return;

        //disable interrupts for this port
        //Serial.print("Disabling interrupt port "); Serial.println(portNum);
        byte portNumBinary = bit(portNum);
        PCIFR &= !portNumBinary;
        PCICR &= !portNumBinary;
        //delete port instance
        delete port;
        ATMEGA_328_INT_PORTS[portNum] = 0;
        //Serial.println("Done disabling port.");
    }

    bool InterruptPort::attachInterrupt(Interrupt * interrupt)
    {
        byte pin = interrupt->getPin();
        byte portPin = digitalPinToPCMSKbit(pin);
        if (mInterrupts[portPin])
            return false;

        byte portPinBinary = bit(portPin);
        *digitalPinToPCMSK(pin) |= portPinBinary; // enable pin

                                                  // set pullups
        pinMode(pin, INPUT);
        digitalWrite(pin, HIGH);
        mLastPortState |= portPinBinary;

        mInterrupts[portPin] = interrupt;

        return true;
    }

    void InterruptPort::deattachInterrupt(Interrupt * interrupt)
    {
        byte pin = interrupt->getPin();
        byte portPin = digitalPinToPCMSKbit(pin);
        byte portPinBinary = bit(portPin);
        *digitalPinToPCMSK(pin) &= ~portPinBinary; // disable pin
        mInterrupts[portPin] = 0;
    }

    void InterruptPort::interruptOccured(byte portState)
    {
        byte changedPins = portState ^ mLastPortState;
        mLastPortState = portState;

        for (byte i = 0; changedPins && i < PINS_PER_PORT; i++, changedPins >>= 1) {
            if (!(changedPins & 1))
                continue;

            Interrupt* interrupt = mInterrupts[i];
            if (!interrupt)
                continue;

            byte pinBinary = bit(i);
            switch (interrupt->getMode()) {
            case ONCHANGE:
                mInterrupts[i]->interruptServiceRoutine();
                break;
            case ONRISING:
                if (portState & pinBinary)
                    mInterrupts[i]->interruptServiceRoutine();
                break;
            }
        }
    }

    bool InterruptPort::hasEnabledPins()
    {
        for (Interrupt* interrupt : mInterrupts)
            if (interrupt)
                return true;
        return false;
    }

    void printInterrupt(Interrupt* interrupt) {
        Serial.print("\nInterrupt on pin: ");
        Serial.println(interrupt->getPin());
    }

    Interrupt::~Interrupt()
    {
        deattachInterrupt(this);
    }
};


// port B ISR; handle pin change interrupt for D8 to D15 here
ISR(PCINT0_vect)
{
    if (ATMEGA_328_INT_PORTS[0])
        ATMEGA_328_INT_PORTS[0]->interruptOccured(PINB);
}

// port C ISR; handle pin change interrupt for A0 to A5 here
ISR(PCINT1_vect)
{
    if (ATMEGA_328_INT_PORTS[1])
        ATMEGA_328_INT_PORTS[1]->interruptOccured(PINC);
}

// port D ISR; handle pin change interrupt for D0 to D7 here
ISR(PCINT2_vect)
{
    if (ATMEGA_328_INT_PORTS[0])
        ATMEGA_328_INT_PORTS[2]->interruptOccured(PIND);
}

