#pragma once

#include "Arduino.h"

class Interrupt {
	byte pin;

public:
	Interrupt(byte pin) : pin(pin) {}
	byte getPin() { return pin; }

	virtual void interruptServiceRoutine() = 0;
};

void printInterrupt(Interrupt* interrupt);

void attachInterrupt(Interrupt* interrupt);
void deattachInterrupt(Interrupt* interrupt);
