// 
// 
// 

#include "Controller2WD.h"

Controller2WD::Controller2WD(double wheelDegreesPerSecond, double wheelRadius, double distanceBetweenWheels, unsigned short power,
	AbstractInterruptor* interruptor) : interruptor(*interruptor)
{
	(*this).wheelDegreesPerMiliSecond = wheelDegreesPerSecond / 1000;
	(*this).wheelRadius = wheelRadius;
	(*this).power = power;
	kitRaduis = distanceBetweenWheels / 2.0;

	leftMotor = Motor(A_DIR, A_PWM, A_BRK);
	rightMotor = Motor(B_DIR, B_PWM, B_BRK);

	UpdateParameters();
}

void Controller2WD::Move(double distance)
{
	bool direction = 0;
	if (distance < 0)
	{
		direction = 1;
		distance = -distance;
	}


	int timeMS = (int)(distance / straightSpeed);
	leftMotor.Move(direction);
	rightMotor.Move(direction);

	Wait(timeMS);
}

void Controller2WD::Turn(double degrees)
{
	bool direction = 0;
	if (degrees < 0.0)
	{
		direction = 1;
		degrees = -degrees;
	}
	if (degrees > 180.0)
	{
		direction = !direction;
		degrees = 360.0 - degrees;
	}

	leftMotor.Move(!direction);
	rightMotor.Move(direction);

	int timeMS = (int)(degrees / turnSpeed);
	Wait(timeMS);
}

void Controller2WD::ChangePower(unsigned short power)
{
	wheelDegreesPerMiliSecond = (wheelDegreesPerMiliSecond / (*this).power) * power;
	(*this).power = power;
	UpdateParameters();
}

void Controller2WD::UpdateParameters()
{
	leftMotor.SetPower(power);
	rightMotor.SetPower(power);

	straightSpeed = (wheelDegreesPerMiliSecond * wheelRadius * M_PI) / 180;
	turnSpeed = (wheelDegreesPerMiliSecond * wheelRadius) / kitRaduis;
}

void Controller2WD::Wait(int milliseconds)
{
	unsigned int step = interruptor.GetCheckTIme();
	while (milliseconds > 0)
	{
		delay(step);
		milliseconds -= step;

		if (interruptor.HasToInterrupt())
			break;
	}

	leftMotor.Stop();
	rightMotor.Stop();
}
