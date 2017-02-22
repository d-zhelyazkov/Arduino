#include "AnalogJoystickController.h"
#include <math.h>


#define MAX_POWER 255
#define MIN_POWER 0


AnalogJoystickController::AnalogJoystickController(Motor* left, Motor* right)
    : mLeftMotor(left), mRightMotor(right) {}


void AnalogJoystickController::move(float x, float y) {
	//x,y are the pad's position
    float xAbs = fabs(x);
    float yAbs = fabs(y);
	if (!x || !y || (xAbs > 1.0) || (yAbs > 1.0)) {
		stop();
		return;
	}

	bool motorsSameDir = (xAbs < yAbs);
	float coef = (motorsSameDir) ? x / y : y / x;

	// the main motor is the leading one
	Motor* mainMotor;
	Motor* secMotor;
	MotorState mainDirection;
	if (coef < 0.0) {
		mainMotor = mRightMotor;
		secMotor = mLeftMotor;
		mainDirection = (y < 0.0) ? MotorState::ROT_ANTI_CLOCK : MotorState::ROT_CLOCK;
	}
	else {
		mainMotor = mLeftMotor;
		secMotor = mRightMotor;
		mainDirection = (y > 0.0) ? MotorState::ROT_ANTI_CLOCK : MotorState::ROT_CLOCK;
	}

	//the power typically is an integer from 0 to 255 or 1024
	unsigned short mainPower = sqrt(x*x + y*y) * (MAX_POWER - MIN_POWER) + MIN_POWER;
	mainMotor->setPower(mainPower);
	mainMotor->setState(mainDirection);

	unsigned short secondaryPower = (1.0 - fabs(coef)) * mainPower;
	secMotor->setPower(secondaryPower);
	secMotor->setState(static_cast<MotorState>(((mainDirection - 1) ^ motorsSameDir) + 1));
    //if (mainDir = ROT_ANTI_CLOCK(2) and sameDir = 1)
    // (2 - 1) ^ 1 + 1 = 1 -> ROT_CLOCK
	//using a mirrored motors in order to make the robot move in a straight line,
	//we need to set oposite move directions
}

void AnalogJoystickController::stop() {
    mLeftMotor->setState(MotorState::STOPPED);
    mRightMotor->setState(MotorState::STOPPED);
}
