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

void Motor::Move(bool direction)
{
	digitalWrite(directionPin, direction); //Establishes forward direction
	digitalWrite(brakePin, LOW);   //Disengage the Brake
}

void Motor::Stop()
{
	digitalWrite(brakePin, HIGH);
}

void Motor::SetPower(unsigned short power)
{
	analogWrite(pwmPin, power);
}
