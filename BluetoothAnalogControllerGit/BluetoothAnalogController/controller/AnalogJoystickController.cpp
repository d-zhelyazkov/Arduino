// 
// 
// 

#include "AnalogJoystickController.h"
#include <math.h>

AnalogJoystickController::AnalogJoystickController() : Abstract2WDController()
{
	x = 0.0;
	y = 0.0;
}

bool AnalogJoystickController::VerifyParameters()
{
	return !((x < -1.0) || (x > 1.0) || (y < -1.0) || (y > 1.0));
}

void AnalogJoystickController::StartMotors() {
	//x,y are the pad's position
	if (!VerifyParameters() || ((x == 0.0) && (y == 0.0))) {
		Stop();
		return;
	}

	bool motorsSameDir = (abs(x) < abs(y));
	float coef = (motorsSameDir) ? x / y : y / x;

	// the main motor is the leading one
	Motor* mainMotor;
	Motor* secMotor;
	bool mainDirection;
	if (coef < 0.0) {
		mainMotor = rightMotor;
		secMotor = leftMotor;
		mainDirection = (y < 0.0);
	}
	else {
		mainMotor = leftMotor;
		secMotor = rightMotor;
		mainDirection = (y > 0.0);
	}

	//the power typically is an integer from 0 to 255 or 1024
	unsigned short mainPower = sqrt(x*x + y*y) * (MAX_POWER - MIN_POWER) + MIN_POWER;
	mainMotor->SetPower(mainPower);
	mainMotor->Move(mainDirection);

	unsigned short secondaryPower = (1.0 - abs(coef)) * mainPower;
	secMotor->SetPower(secondaryPower);
	secMotor->Move((mainDirection ^ motorsSameDir));
	//using a mirrored motors in order to make the robot move in a straight line,
	//we need to set oposite move directions
}
