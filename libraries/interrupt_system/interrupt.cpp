#include "Interrupt.h"
#include "pins_arduino.h"
#include "InterruptPort.h"

InterruptPort* ATMEGA_328_INT_PORTS[3] = { 0 };		//ports B(0), C(1), D(2)

void attachInterrupt(Interrupt * interrupt)
{
    byte pin = interrupt->getPin();

    byte portNum = digitalPinToPCICRbit(pin);
    InterruptPort* port = ATMEGA_328_INT_PORTS[portNum];
    if (!port) {
        Serial.printf("Enabling interrupt port %hhu.\n", portNum);
        port = ATMEGA_328_INT_PORTS[portNum] = new InterruptPort();
        byte portNumBinary = bit(portNum);
        PCIFR |= portNumBinary; // clear any outstanding interrupt
        PCICR |= portNumBinary; // enable interrupts for the port 
    }

    Serial.printf("Attaching interrupt on pin %hhu to port %hhu\n", pin, portNum);
    port->attachInterrupt(interrupt);
}

void deattachInterrupt(Interrupt * interrupt)
{
    byte pin = interrupt->getPin();
    byte portNum = digitalPinToPCICRbit(pin);
    InterruptPort* port = ATMEGA_328_INT_PORTS[portNum];
    if (!port)
        return;

    Serial.print("Deattaching interrupt pin "); Serial.print(pin); Serial.print(" from port "); Serial.println(portNum);
    port->deattachInterrupt(interrupt);
    //Serial.println("Done disabling pin.");

    if (port->hasEnabledPins())
        return;

    //disable interrupts for this port
    Serial.print("Disabling interrupt port "); Serial.println(portNum);
    byte portNumBinary = bit(portNum);
    PCIFR &= !portNumBinary;
    PCICR &= !portNumBinary;
    //delete port instance
    delete port;
    ATMEGA_328_INT_PORTS[portNum] = 0;
    //Serial.println("Done disabling port.");
}

void printInterrupt(Interrupt* interrupt) {
    Serial.print("\nInterrupt on pin: ");
    Serial.println(interrupt->getPin());
}


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

void Interrupt::attach() {
    attachInterrupt(this);
}

void Interrupt::deattach() {
    deattachInterrupt(this);
}
