/*
 Name:		AngularController.ino
 Created:	2/13/2016 5:20:08 PM
 Author:	XRC_7331
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "libs\controller\AngularController.h"
#include "libs\compass\AdafruitCompass.h"
#include "libs\interruptor\WaitInterruptor.h"

Compass* compass;
AngularController* controller;
WaitInterruptor* interruptor;

// the setup function runs once when you press reset or power the board
void setup() {
	compass = new AdafruitCompass();
	controller = new AngularController(compass);
	interruptor = new WaitInterruptor(1000);
	//controller->reset();
	Serial.begin(9600);
	Serial.println("gimme a degree: ");

}

// the loop function runs over and over again until power down or reset
void loop() {
	//Serial.println("\ngimme a degree: ");
	delay(2000);
	if (Serial.available()) {
		int currPos = smoothAngle(compass->getDirectionInDegrees());
		Serial.print("currPos: ");
		Serial.println(currPos);

		int degree = Serial.parseInt();
		Serial.print("accepted: ");
		Serial.println(degree);

		controller->turn(degree);
		controller->setInterruptor(interruptor);
		controller->move();
		delay(1000);
		currPos = smoothAngle(compass->getDirectionInDegrees());
		Serial.print("newPos: ");
		Serial.println(currPos);

		Serial.println("gimme a degree: ");
	}
}
