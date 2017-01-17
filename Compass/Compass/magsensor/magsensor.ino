

//#include <Adafruit_Sensor\Adafruit_Sensor.h>
//#include "compass\AdafruitCompass.h"
//#include <Adafruit_HMC5883_Unified\Adafruit_HMC5883_U.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#include "compass\MPUCompass.h"

Compass* compass;

void setup(void)
{
	Serial.begin(9600);

	//compass = new AdafruitCompass();
	compass = new MPUCompass();

	Serial.println("Compass Test");
}

void loop(void)
{
	float degree = compass->getDirectionInDegrees();
	Serial.println(degree);
	delay(1000);

}


