// AngularController.h
#pragma once

#include "arduino.h"

#include "Abstract2WDController.h"
#include "compass.h"


class AngularController2 : public Abstract2WDController
{
private:
	Compass* compass;
	float sumV = 0;
	float lastV = 0;
	float totalDistanceTurned = 0;
	unsigned long totalMSTurned = 0;
	unsigned int turnsMade = 0;

	float turnTime(unsigned long ms);
public:
	AngularController2(Compass* compass);
	void reset();
	float turn(float angle);
	void turnTo(float newPos);
	float getV();

	float getTotalDistance() { return totalDistanceTurned; }
	unsigned long getTotalTime() { return totalMSTurned; }
	float getLastV() { return lastV; }
};


