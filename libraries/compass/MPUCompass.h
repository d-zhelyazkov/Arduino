#pragma once

#include "compass.h"
#include "Arduino.h"
#include "MPU6050_6Axis_MotionApps20.h"

//SCL - A5, SDA - A4
class MPUCompass :
	public Compass
{
public:
	MPUCompass(byte interruptPin);
	~MPUCompass();

	void startListening();
	void stopListening();

	float getDirectionInRadians();
};
