// 
// 
// 

#include "TestController.h"

TestController::TestController() : Abstract2WDController() {}

void TestController::StartMotors()
{
	short power = MAX_POWER >> 1;
	leftMotor->SetPower(power);
	rightMotor->SetPower(power);
	leftMotor->Move(1);
	rightMotor->Move(0);
}
