#include "Motor.h"

Motor::Motor(byte directionPin, byte pwmPin, byte brakePin) :
	directionPin(directionPin)
	, pwmPin(pwmPin)
	, brakePin(brakePin)
{
	pinMode(directionPin, OUTPUT);
	pinMode(brakePin, OUTPUT);
}

void Motor::move(State direction) 
{
	state = direction;

	byte dir;
	switch (direction) {
	case State::STOPPED:
		return;
	case State::ROT_CLOCK:
		dir = 0;
		break;
	case State::ROT_ANTI_CLOCK:
		dir = 1;
		break;
	}

	digitalWrite(directionPin, dir); //Establishes direction
	digitalWrite(brakePin, LOW);   //Disengage the Brake
}

void Motor::stop()
{
	digitalWrite(brakePin, HIGH);
	state = State::STOPPED;
}

void Motor::setPower(byte power)
{
	analogWrite(pwmPin, power);
	stop();
}

State Motor::getState()
{
	return state;
}
