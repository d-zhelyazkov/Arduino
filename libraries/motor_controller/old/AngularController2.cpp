// 
// 
// 

#include "AngularController2.h"
#include "WaitInterruptor.h"

#define DEFEFAULT_POSITION 0.0
#define PI_DEG 180
#define PI_DEGx2 360

#define INCLUDE_IGNORE 1
#define IGNORE_DIST 10

#define COMPASS_WAIT 1000

#define INIT_TESTS 3
#define INIT_TEST_TIME 100
#define INIT_TEST_STEP 200
#define INIT_TEST_ANGLE 45
#define INIT_TEST_ANGLE_K 2

AngularController2::AngularController2(Compass* compass) : Abstract2WDController()
{
	this->compass = compass;
	aMotor->SetPower(MAX_POWER);
	bMotor->SetPower(MAX_POWER);

	this->steerDirection = SteerDirection::RIGHT;
	unsigned long ms = INIT_TEST_TIME;
	uint8_t i;
	for (i = 0; i < INIT_TESTS; i++) {
		turnTime(ms);
		Serial.println(ms);
		ms += INIT_TEST_STEP;
	}
	float turnAngle = INIT_TEST_ANGLE;
	for (i = 0; i < INIT_TESTS; i++) {
		turn(turnAngle);
		turnAngle *= INIT_TEST_ANGLE_K;
	}

	this->steerDirection = SteerDirection::FORWARD;
}

void AngularController2::reset()
{
	this->turnTo(DEFEFAULT_POSITION);
}


float AngularController2::turn(float angle) {
	angle = fmod(angle, PI_DEGx2);
	if (angle < 0) {
		angle += PI_DEGx2;
	}
	else if (angle > PI_DEGx2) {
		angle -= PI_DEGx2;
	}

	float distance = 0;
	if (angle < PI_DEG) {
		this->steerDirection = SteerDirection::RIGHT;
		distance = angle;
	}
	else {
		distance = PI_DEGx2 - angle;
		this->steerDirection = SteerDirection::LEFT;
	}

	float turnedDistance = 0;
	if (!INCLUDE_IGNORE || distance > IGNORE_DIST) {


		turnedDistance = turnTime(distance / getV());
	}

	this->steerDirection = SteerDirection::FORWARD;
	return turnedDistance;
}

float AngularController2::getV() {
	//float V = sumV / turnsMade;
	float V = lastV;
	//float V = totalDistanceTurned / totalMSTurned;

	return V;
}

float AngularController2::turnTime(unsigned long ms) {
	float currDir = compass->getDirectionInDegrees();
	WaitInterruptor wait(ms);
	this->setInterruptor(&wait);
	this->move();
	/*delay(ms);
	this->stop();*/

	delay(COMPASS_WAIT);
	float newDir = compass->getDirectionInDegrees();

	float distance = (this->steerDirection == SteerDirection::RIGHT) ? newDir - currDir : currDir - newDir;
	if (distance < 0)
		distance += PI_DEGx2;

	turnsMade++;
	lastV = distance / ms;
	totalDistanceTurned += distance;
	totalMSTurned += ms;
	sumV += lastV;

	return distance;
}

void AngularController2::turnTo(float newPos) {
	turn(newPos - compass->getDirectionInDegrees());
}
