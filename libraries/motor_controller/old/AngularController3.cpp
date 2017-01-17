#include "AngularController3.h"
#include "WaitInterruptor.h"
#include "ExStream.h"

#define STEP_K_MS 50
#define COMPASS_WAIT 1000

#define PI_DEG 180
#define PI_DEGx2 360

#define INCLUDE_IGNORE 1
#define IGNORE_DIST 10

AngularController3::AngularController3(Compass * compass)
{
	aMotor->SetPower(MIN_POWER);
	bMotor->SetPower(MIN_POWER);

	ExStream* stream = ExStream::getInstance(0);
	this->steerDirection = SteerDirection::RIGHT;
	statistics[0] = 0;
	for (uint8_t i = 1; i < STATISTIC_SIZE; i++) {
		float currDir = compass->getDirectionInDegrees();
		WaitInterruptor wait(i * STEP_K_MS);
		this->setInterruptor(&wait);
		this->move();

		delay(COMPASS_WAIT);
		float newDir = compass->getDirectionInDegrees();

		float distance = newDir - currDir;
		if (distance < 0)
			distance += PI_DEGx2;

		statistics[i] = distance;
		if (stream) {
			stream->print(i);
			stream->print(" ");
			stream->println(distance);
		}
	}
}

AngularController3::~AngularController3()
{
}

float AngularController3::turn(float angle)
{
	ExStream* stream = ExStream::getInstance(0);

	angle = fmod(angle, PI_DEGx2);
	if (angle < 0) {
		angle += PI_DEGx2;
	}
	else if (angle > PI_DEGx2) {
		angle -= PI_DEGx2;
	}

	if (angle < PI_DEG) {
		this->steerDirection = SteerDirection::RIGHT;
	}
	else {
		angle = PI_DEGx2 - angle;
		this->steerDirection = SteerDirection::LEFT;
	}
	if (INCLUDE_IGNORE && angle < IGNORE_DIST) {
		angle = 0;
	}
	else {
		uint16_t turnTime = 0;
		for (uint8_t i = 1; i < STATISTIC_SIZE; i++) {
			if (angle < statistics[i]) {
				float angleDiff = angle - statistics[i - 1];
				float stepDiff = statistics[i] - statistics[i - 1];
				float k = angleDiff / stepDiff;
				float n = i - 1 + k;
				turnTime = n * STEP_K_MS;

				if (stream) {
					stream->print("angleDiff: "); stream->println(angleDiff);
					stream->print("stepDiff: "); stream->println(stepDiff);
					stream->print("k: "); stream->println(k);
					stream->print("n: "); stream->println(n);
					stream->print("time: "); stream->println(turnTime);
				}

				break;
			}
		}

		if (!turnTime) {
			turnTime = STATISTIC_SIZE * STEP_K_MS;
		}

		WaitInterruptor wait(turnTime);
		this->setInterruptor(&wait);
		this->move();
	}
	this->steerDirection = SteerDirection::FORWARD;
	return angle;
}

