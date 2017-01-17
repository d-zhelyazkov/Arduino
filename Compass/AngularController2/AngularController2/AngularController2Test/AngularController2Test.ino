/*
Name:		AngularController.ino
Created:	2/13/2016 5:20:08 PM
Author:	XRC_7331
*/

#include <Wire.h>

/*#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>*/
//#include "libs\compass\AdafruitCompass.h"

#include "libs\controller\AngularController2.h"

#include "SoftwareSerial.h"
#include "libs\ExSoftwareSerial.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "libs\compass\MPUCompass.h"

#define BT_RX 4
#define BT_TX 5

Compass* compass;
AngularController2* controller;
ExSoftwareSerial btStream(BT_RX, BT_TX);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	btStream.begin(9600);

	compass = new MPUCompass();
	btStream.print("compass init ");
	btStream.println(compass->getDirectionInDegrees());

	controller = new AngularController2(compass);
	//controller->reset();
	btStream.println("gimme a degree: ");

}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//Serial.println("\ngimme a degree: ");
	delay(2000);
	if (!btStream.available())
		return;

	btStream.print("compass: ");
	btStream.println(compass->getDirectionInDegrees());

	btStream.print("last V: ");
	btStream.println(controller->getLastV());
	btStream.print("travelled distance: ");
	btStream.println(controller->getTotalDistance());
	btStream.print("travelled time: ");
	btStream.println(controller->getTotalTime());

	int currPos = smoothAngle(compass->getDirectionInDegrees());
	btStream.print("currPos: ");
	btStream.println(currPos);

	int degree = btStream.parseInt();
	btStream.print("accepted: ");
	btStream.println(degree);

	btStream.print("speed: ");
	float V = controller->getV();
	btStream.println(V);
	btStream.print("expected turn time: ");
	btStream.println(degree / V);

	float distanceTravelled = controller->turn(degree);
	btStream.print("distance travelled: ");
	btStream.println(distanceTravelled);
	//controller->setInterruptor(interruptor);
	//controller->move();
	delay(1000);
	currPos = smoothAngle(compass->getDirectionInDegrees());
	btStream.print("newPos: ");
	btStream.println(currPos);

	btStream.print("compass: ");
	btStream.println(compass->getDirectionInDegrees());

	btStream.println("gimme a degree: ");
	
}
