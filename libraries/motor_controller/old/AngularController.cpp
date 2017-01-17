// 
// 
// 

#include "AngularController.h"
#include "Range.h"
#include "CompassRangeInterruptor.h"
#include "ExStream.h"

#define INCLUDE_IGNORE 0
#define IGNORE_DIFF 10

#define PIx2 6.283
#define PI_DEG 180
#define PI_DEGx2 360

float smoothAngle(float value)
{
	/*if (value < -PI) {
		value += PIx2;
	}
	else if (value > PI) {
		value -= PIx2;
	}*/
	//now value e [-PI;PI]

	if (value < 0) {
		value += PI_DEGx2;
	}
	else if (value >= PI_DEGx2){
		value -= PI_DEGx2;
	}

	//[0,360)
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

//angle - in degrees
void AngularController::turn(float angle) {
	turnTo(compass->getDirectionInDegrees() + angle);
}

//angle - in degrees
void AngularController::turnTo(float newPos) {
	ExStream* stream = ExStream::getInstance(0);

	newPos = fmod(newPos, PI_DEGx2);
	newPos = smoothAngle(newPos);

	float currPos = compass->getDirectionInDegrees();

	if (stream) {
		stream->print("Current: "); stream->println(currPos);
		stream->print("new: "); stream->println(newPos);
	}
	/*float diff = fabs(fmod(newPos - currPos, PI));
	if (INCLUDE_IGNORE && diff < IGNORE_DIFF)
		return;

	Serial.print("\ncurrPos: ");
	Serial.println(radToDeg(currPos));
	Serial.print("\nnewPos: ");
	Serial.println(radToDeg(newPos));
	Serial.print("\ndiff: ");
	Serial.println(radToDeg(diff));*/

	Range* range = NULL;

	if (newPos > PI_DEG) {
		range = new Range(newPos - PI_DEG, newPos);
		if (range->isInRange(currPos)) {
			this->steerDirection = SteerDirection::RIGHT;
			if (INCLUDE_IGNORE) range->setHigherBound(smoothAngle(newPos - IGNORE_DIFF));
			range->setCheckType(CheckType::INNER);
		}
		else {
			this->steerDirection = SteerDirection::LEFT;
			if (INCLUDE_IGNORE) range->setHigherBound(smoothAngle(newPos + IGNORE_DIFF));
			range->setCheckType(CheckType::OUTER);

		}
	}
	else {
		range = new Range(newPos, newPos + PI_DEG);
		if (range->isInRange(currPos)) {
			this->steerDirection = SteerDirection::LEFT;
			if (INCLUDE_IGNORE) range->setLowerBound(smoothAngle(newPos + IGNORE_DIFF));
			range->setCheckType(CheckType::INNER);
		}
		else {
			this->steerDirection = SteerDirection::RIGHT;
			if (INCLUDE_IGNORE) range->setLowerBound(smoothAngle(newPos - IGNORE_DIFF));
			range->setCheckType(CheckType::OUTER);
		}
	}

	if (stream) {
		stream->print("Range: "); stream->print(range->getLowerBound()); 
		stream->print(" "); stream->println(range->getHigherBound());
		stream->print("Check: "); stream->println(getCheckTypeStr(range->getCheckType()));
		stream->print("Direction: "); stream->println(getSteerDirectionStr(steerDirection));
	}

	CompassRangeInterruptor* interruptor = new CompassRangeInterruptor(this->compass, range);
	this->setInterruptor(interruptor);

	this->move();

	delete(range);
	delete(interruptor);
	/*
	newPos = compass->getDirectionInRadians();
	diff = fabs(fmod(newPos - currPos, PI));
	Serial.print("\ncurrPos ");
	Serial.println(radToDeg(newPos));
	Serial.print("\nmade ");
	Serial.print(radToDeg(diff));
	Serial.println(" degrees");
	delete(interruptor);*/
}
