/*
 Name:		AngularController2Test.ino
 Created:	7/10/2016 9:00:32 PM
 Author:	XRC_7331
*/

#include "Wire.h"
#include "SoftwareSerial.h"
#include "ExStream.h"

#include "controller\AngularController2.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPUCompass.h"

#define BT_RX 4
#define BT_TX 5

Compass* compass;
AngularController2* controller;
ExStream* btStream;

// the setup function runs once when you press reset or power the board
void setup() {
	SoftwareSerial* btSerial = new SoftwareSerial(BT_RX, BT_TX);
	btSerial->begin(9600);
	btStream = new ExStream(btSerial);

	compass = new MPUCompass();
	controller = new AngularController2(compass);

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

