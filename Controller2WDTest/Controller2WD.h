// Controller2WD.h

#ifndef _CONTROLLER2WD_h
#define _CONTROLLER2WD_h

#include "Motor.h"
#include <math.h>
#include "AbstractInterruptor.h"


#define B_DIR 13
#define B_PWM 11
#define B_BRK 8
#define A_DIR 12
#define A_PWM 3
#define A_BRK 9


class Controller2WD
{
private:
	Motor leftMotor;
	Motor rightMotor;
	AbstractInterruptor& interruptor;

	double straightSpeed;
	double turnSpeed;
	double wheelDegreesPerMiliSecond;
	double wheelRadius;
	double kitRaduis;
	unsigned short power;

	void UpdateParameters();
	void Wait(int milliseconds);

public:
	Controller2WD(double wheelDegreesPerSecond, double wheelRadius, double distanceBetweenWheels, unsigned short power, AbstractInterruptor* interruptor);

	void Move(double distance);
	void Turn(double degrees);
	void ChangePower(unsigned short power);
};

#endif

