#pragma once

#include "Arduino.h"

enum InterruptMode{ONCHANGE, ONRISING};

class Interrupt {
	byte pin;
	InterruptMode mode = ONCHANGE;

public:
	Interrupt(byte pin) : pin(pin) {}
	Interrupt(byte pin, InterruptMode mode) : pin(pin), mode(mode) {}

	byte getPin() { return pin; }
	InterruptMode getMode() { return mode; }

	virtual void interruptServiceRoutine() = 0;
};

void printInterrupt(Interrupt* interrupt);

void attachInterrupt(Interrupt* interrupt);
void deattachInterrupt(Interrupt* interrupt);
