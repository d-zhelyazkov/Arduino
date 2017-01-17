/*
 Name:		AngularController.ino
 Created:	2/13/2016 5:20:08 PM
 Author:	XRC_7331
*/

#include <Wire.h>
#include "SoftwareSerial.h"
#include "ExStream.h"
#include "Range.h"
#include "CompassRangeInterruptor.h"
#include "AngularController.h"

//#include <Adafruit_Sensor.h>
//#include <Adafruit_HMC5883_U.h>
//#include "compass\AdafruitCompass.h"
//#include "interruptor\WaitInterruptor.h"


#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPUCompass.h"

#define BT_RX 4
#define BT_TX 5

Compass* compass;
AngularController* controller;
ExStream* btStream;

// the setup function runs once when you press reset or power the board
void setup() {
	compass = new MPUCompass();
	controller = new AngularController(compass);

	SoftwareSerial* btSerial = new SoftwareSerial(BT_RX, BT_TX);
	btSerial->begin(9600);
	btStream = ExStream::createInstance(0, btSerial);
}

// the loop function runs over and over again until power down or reset
void loop() {
	btStream->println("\ngimme a degree: ");
	while (!btStream->available());
	delay(1000);

	btStream->print("\n\tcompass: "); btStream->println(compass->getDirectionInDegrees());

	long degree = btStream->parseInt_W();
	btStream->println(degree);
	controller->turn(degree);

	btStream->print("\n\tcompass: "); btStream->println(compass->getDirectionInDegrees());
}
