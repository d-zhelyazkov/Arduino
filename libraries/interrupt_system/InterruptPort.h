// InterruptPort.h
#pragma once

#include "Interrupt.h"
#include "Arduino.h"

#define PINS_PER_PORT 8

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


