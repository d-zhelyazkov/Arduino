#include "MotorWithEncoder.h"
#include "Interrupt.h"

class MotorEncoderInterrupt : public Interrupt {
	MotorWithEncoder* motor;
	uint16_t ticks = 0;
	uint16_t tickLimit;
public:
	MotorEncoderInterrupt(MotorWithEncoder* motor, byte pin, uint16_t tickLimit) 
		: Interrupt(pin), motor(motor), tickLimit(tickLimit) {}

	void interruptServiceRoutine() {
		//Serial.print("Interrupt occured on pin "); Serial.println(getPin());

		ticks++;
		//Serial.print("Ticks: "); Serial.println(ticks);
		if (ticks < tickLimit)
			return;

		//Serial.print("Disabling interript on pin "); Serial.println(getPin());
		deattachInterrupt(this);
		motor->stop();
		delete this;
	}
};

MotorWithEncoder::MotorWithEncoder(byte directionPin, byte pwmPin, byte brakePin, byte encoderPin)
	: Motor(directionPin, pwmPin, brakePin), encoderPin(encoderPin){}

void MotorWithEncoder::move(State direction, uint16_t encoderTicks)
{
	MotorEncoderInterrupt* interrupt = new MotorEncoderInterrupt(this,encoderPin, encoderTicks);
	attachInterrupt(interrupt);
	((Motor*)this)->move(direction);
}
