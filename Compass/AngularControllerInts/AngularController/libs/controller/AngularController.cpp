// 
// 
// 

#include "AngularController.h"
#include "libs/tools/Range.h"
#include "libs\interruptor\CompassRangeInterruptor.h"

#define INCLUDE_IGNORE 1
#define IGNORE_DIFF 10
#define PI_DEG 180

const int PI_DEGx2 = (PI_DEG << 1);

float smoothAngle(int value)
{
	if (value < 0) {
		value += PI_DEGx2;
	}
	else if (value > PI_DEGx2) {
		value -= PI_DEGx2;
	}
	//now value e [0;360]

	return value;
}

float radToDeg(float rad)
{
	return (rad * 180) / PI;
}

AngularController::AngularController(Compass * compass) : Abstract2WDController()
{
	this->compass = compass;
	aMotor->SetPower(MIN_POWER);
	bMotor->SetPower(MIN_POWER);
}

void AngularController::reset()
{
	this->turnTo(DEFEFAULT_POSITION);
}


void AngularController::turn(int angle) {
	turnTo(compass->getDirectionInDegrees() + angle);
}
void AngularController::turnTo(int newPos) {
	newPos = newPos % PI_DEGx2;
	newPos = smoothAngle(newPos);

	int currPos = compass->getDirectionInDegrees();
	int diff = abs(newPos - currPos);
	if (diff > PI_DEG)
		diff -= PI_DEG;

	if (INCLUDE_IGNORE && diff < IGNORE_DIFF)
		return;

	/*Serial.print("\ncurrPos: ");
	Serial.println(currPos);
	Serial.print("\nnewPos: ");
	Serial.println(newPos);
	Serial.print("\ndiff: ");
	Serial.println(diff);*/

	Range* range = NULL;

	if (newPos >= PI_DEG) {
		range = new Range(newPos - PI_DEG, newPos);
		if (range->isInRange(currPos)) {
			this->turnDirection = TurnDirection::RIGHT;
			range->setDefaultCheckType(CheckType::INNER);
			if (INCLUDE_IGNORE) range->setHigherBound(smoothAngle(newPos - IGNORE_DIFF));
		}
		else {
			this->turnDirection = TurnDirection::LEFT;
			range->setDefaultCheckType(CheckType::OUTER);
			if (INCLUDE_IGNORE) range->setHigherBound(smoothAngle(newPos + IGNORE_DIFF));

		}
	}
	else {
		range = new Range(newPos, newPos + PI_DEG);
		if (range->isInRange(currPos)) {
			this->turnDirection = TurnDirection::LEFT;
			range->setDefaultCheckType(CheckType::INNER);
			if (INCLUDE_IGNORE) range->setLowerBound(smoothAngle(newPos + IGNORE_DIFF));
		}
		else {
			this->turnDirection = TurnDirection::RIGHT;
			range->setDefaultCheckType(CheckType::OUTER);
			if (INCLUDE_IGNORE) range->setLowerBound(smoothAngle(newPos - IGNORE_DIFF));
		}
	}
	CompassRangeInterruptor* interruptor = new CompassRangeInterruptor(this->compass, range);
	this->setInterruptor(interruptor);

	this->move();

	/*delay(1000);
	newPos = compass->getDirectionInDegrees();
	diff = abs(newPos - currPos);
	if (diff > PI_DEG)
		diff -= PI_DEG;
	Serial.print("\ncurrPos ");
	Serial.println(newPos);
	Serial.print("\nmade ");
	Serial.print(diff);
	Serial.println(" degrees");*/

	this->turnDirection = TurnDirection::NONE;
	delete(interruptor);
}

void AngularController::startMotors() {
	switch (turnDirection)
	{
	case NONE:
		aMotor->Move(MoveDirection::FORWARD);
		bMotor->Move(MoveDirection::FORWARD);
		break;
	case LEFT:
		bMotor->Move(MoveDirection::FORWARD);
		break;
	case RIGHT:
		aMotor->Move(MoveDirection::FORWARD);
		break;
	}
}