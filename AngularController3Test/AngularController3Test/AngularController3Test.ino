/*
 Name:		AngularController3Test.ino
 Created:	7/10/2016 11:24:34 PM
 Author:	XRC_7331
*/

#include "Wire.h"
#include "SoftwareSerial.h"
#include "ExStream.h"

#include <AngularController3.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPUCompass.h"

#define BT_RX 4
#define BT_TX 5

Compass* compass;
AngularController3* controller;
ExStream* btStream;

// the setup function runs once when you press reset or power the board
void setup() {
	SoftwareSerial* btSerial = new SoftwareSerial(BT_RX, BT_TX);
	btSerial->begin(9600);
	btStream = ExStream::createInstance(0,btSerial);

	compass = new MPUCompass();
	controller = new AngularController3(compass);

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


