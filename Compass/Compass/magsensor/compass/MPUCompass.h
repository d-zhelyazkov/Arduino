#ifndef MPU_COMPASS
#define MPU_COMPASS
#include "compass.h"

#include "MPU6050_6Axis_MotionApps20.h"

//SCL - A5, SDA - A4
class MPUCompass :
	public Compass
{
	// class default I2C address is 0x68
	// specific I2C addresses may be passed as a parameter here
	// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
	// AD0 high = 0x69
	MPU6050* mpu;
	//MPU6050 mpu(0x69); // <-- use for AD0 high

public:
	MPUCompass();
	~MPUCompass();

	float getDirectionInRadians();
};

#endif