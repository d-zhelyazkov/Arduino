// 
// 
// 

#include "Motor.h"


Motor::Motor(unsigned short directionPin, unsigned short pwmPin, unsigned short brakePin)
{
	Motor::brakePin = brakePin;
	Motor::pwmPin = pwmPin;
	Motor::directionPin = directionPin;

	pinMode(directionPin, OUTPUT);
	pinMode(brakePin, OUTPUT);
}

void Motor::Move(MoveDirection direction) const
{
	digitalWrite(directionPin, direction); //Establishes direction
	digitalWrite(brakePin, LOW);   //Disengage the Brake
}

void Motor::Stop() const
{
	digitalWrite(brakePin, HIGH);
}

void Motor::SetPower(unsigned short power) const
{
	analogWrite(pwmPin, power);
	Stop();
}
