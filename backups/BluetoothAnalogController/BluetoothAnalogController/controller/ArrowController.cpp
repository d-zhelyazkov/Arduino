// 
// 
// 

#include "ArrowController.h"

ArrowController::ArrowController() : Abstract2WDController() {
	short power = MAX_POWER >> 1;
	leftMotor.SetPower(power);
	rightMotor.SetPower(power);
	leftMotor.Stop();
	rightMotor.Stop();
	dir = MoveDir::UNDEF;
}

void ArrowController::StartMotors()
{
	switch (dir)
	{
	case FORWARD:
		leftMotor.Move(1);
		rightMotor.Move(0);
		break;
	case BACKWARD:
		leftMotor.Move(0);
		rightMotor.Move(1);
		break;
	case LEFT:
		leftMotor.Move(1);
		break;
	case RIGHT:
		rightMotor.Move(0);
		break;
	}
}
