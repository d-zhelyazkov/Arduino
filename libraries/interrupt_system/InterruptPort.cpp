#include "InterruptPort.h"
#include "pins_arduino.h"

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
			if(portState & pinBinary)
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
