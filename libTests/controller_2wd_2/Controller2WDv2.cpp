
#include "Controller2WDv2.h"
#include "eeprom_ex.h"

#define WAIT_STOP while (!isStopped()) delay(100);

#define LEARN_STEP 5
#define COMPASS_WAIT 1000

//Controller states regarding Motor states - STATE[leftMotor->state][rightMotor->state]
ControllerState STATES[3][3] =
{ { ControllerState::STILL, ControllerState::TURNING_LEFT, ControllerState::TURNING_RIGHT},
{ ControllerState::TURNING_LEFT,ControllerState::TURNING_LEFT, ControllerState::MOOVING_BACKWARD},
{ ControllerState::TURNING_RIGHT, ControllerState::MOOVING_FORWARD, ControllerState::TURNING_RIGHT } };



Controller2WDv2::Controller2WDv2(MotorWithEncoder * leftMotor, MotorWithEncoder * rightMotor, Compass * compass)
	:leftMotor(leftMotor), rightMotor(rightMotor), compass(compass) {}

void Controller2WDv2::learn()
{
	Serial.println("\nStarted learning.");
	eeprom_clear();

	short degrees = 0;
	for (uint16_t ticks = LEARN_STEP; degrees < PI_DEG; ticks += LEARN_STEP) {
		float currDir = compass->getDirectionInDegrees();
		//Serial.print("Curr: "); Serial.println(currDir);
		turn(ticks, ControllerState::TURNING_RIGHT);
		delay(COMPASS_WAIT);
		float newDir = compass->getDirectionInDegrees();
		//Serial.print("New: "); Serial.println(newDir);
		degrees = newDir - currDir;
		if (degrees < 0)
			degrees += PI_DEGx2;

		eeprom_set(degrees, ticks);
		Serial.print("Learned degrees "); Serial.print(degrees); Serial.print(" for ticks "); Serial.println(ticks);
	}

	Serial.println("\nLearning finished.");
}

void Controller2WDv2::turn(uint16_t encoderTicks, ControllerState turnDir)
{
	WAIT_STOP

	MotorState wheelsRotationDir;
	switch (turnDir)
	{
	case ControllerState::TURNING_LEFT:
			wheelsRotationDir = MotorState::ROT_CLOCK;
		break;
	case ControllerState::TURNING_RIGHT:
		wheelsRotationDir = MotorState::ROT_ANTI_CLOCK;
		break;
	default:
		return;
	}

	leftMotor->move(wheelsRotationDir, encoderTicks);
	rightMotor->move(wheelsRotationDir, encoderTicks);

	WAIT_STOP
}


void Controller2WDv2::turn(short degrees) {
	degrees = degrees % PI_DEGx2;
	if (degrees < 0) {
		degrees += PI_DEGx2;
	}
	else if (degrees > PI_DEGx2) {
		degrees -= PI_DEGx2;
	}

	ControllerState turningDirection;
	if (degrees < PI_DEG) {
		turningDirection = ControllerState::TURNING_RIGHT;
	}
	else {
		degrees = PI_DEGx2 - degrees;
		turningDirection = ControllerState::TURNING_LEFT;
	}

	uint16_t ticks = 0;
	eeprom_get(degrees, ticks);
	if (!ticks) {
		//finding upper bound
		byte upperDegree = degrees;
		uint16_t upperTicks = 0;
		do {
			upperDegree++;
			eeprom_get(upperDegree, upperTicks);
		} while (!upperTicks);

		//finding lower bound
		byte lowerDegree = degrees;
		uint16_t lowerTicks = 0;
		do {
			lowerDegree--;
			eeprom_get(lowerDegree, lowerTicks);
		} while (lowerDegree && (!lowerTicks || lowerTicks >= upperTicks));

		ticks = lowerTicks + (upperTicks - lowerTicks) * ((float)(degrees - lowerDegree)) / (upperDegree - lowerDegree);
	}

	Serial.print("Computed ticks "); Serial.print(ticks); Serial.print(" in direction ");
	switch (turningDirection) {
	case TURNING_LEFT:
		Serial.println("LEFT");
		break;
	case TURNING_RIGHT:
		Serial.println("RIGHT");
		break;
	}
	//float currDir = compass->getDirectionInDegrees();
	turn(ticks, turningDirection);
	/*float newDir = compass->getDirectionInDegrees();
	short degreesMade = newDir - currDir;
	if (degreesMade < 0)
		degreesMade += PI_DEGx2;

	eeprom_set(degreesMade, ticks);*/
}

void Controller2WDv2::move(short ticks)
{
	WAIT_STOP

	ControllerState moveDirection;
	if (ticks < 0) {
		ticks = -ticks;

		leftMotor->move(ROT_CLOCK, ticks);
		rightMotor->move(ROT_ANTI_CLOCK, ticks);
	}
	else {
		leftMotor->move(ROT_ANTI_CLOCK, ticks);
		rightMotor->move(ROT_CLOCK, ticks);
	}

	WAIT_STOP
}

ControllerState Controller2WDv2::getState()
{
	return STATES[leftMotor->getState()][rightMotor->getState()];
}

bool Controller2WDv2::isStopped()
{
	return getState() == ControllerState::STILL;
}


