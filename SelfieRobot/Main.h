#pragma once

#include "controller\AngularController3.h"
//#include "libs\compass\AdafruitCompass.h"
#include "interruptor\WaitInterruptor.h"
#include "libs\geometry\geometry.h"
#include "ExStream.h"
#include "target_finder.h"
#include "MPUCompass.h"

#define BT_RX 4
#define BT_TX 5
#define RECEIVE_ELEMENTS 6

#define LOOP_DELAY 100
#define DISTANCE_THRESHOLD 2
#define FORWARD_MS 1000


void printPoint(Point*);

class Main {
private:
	char DATA_PROCESSED = 0;
	char DATA_RECEIVE_PROBLEM = 1;
	char FIND_ME_REQUEST = 2;

	TargetFinder targetFinder;

	Point headPoint, sidePoint1, sidePoint2;
	ExStream* btStream;
	AngularController3* controller;

public:
	Main() {}

	void init() {
		SoftwareSerial* btSerial = new SoftwareSerial(BT_RX, BT_TX);
		btSerial->begin(9600);
		btStream = new ExStream(btSerial);
		//btStream = ExStream::createInstance(0,btSerial);
		controller = new AngularController3(new MPUCompass());
	}

	void loopBody() {
		btStream->print(FIND_ME_REQUEST);
		delay(LOOP_DELAY);
		if (!btStream->available())
			return;

		Serial.println("Data available!");
		long receiveElements[RECEIVE_ELEMENTS];
		uint8_t receiveResult = btStream->readObjects<long>(receiveElements, RECEIVE_ELEMENTS);
		if (receiveResult) {
			Serial.print("Receive error: ");
			Serial.println(receiveResult);
			btStream->print(DATA_RECEIVE_PROBLEM);
			return;
		}
		btStream->print(DATA_PROCESSED);

		headPoint = Point(receiveElements[0], receiveElements[1]);
		printPoint(&headPoint);
		sidePoint1 = Point(receiveElements[2], receiveElements[3]);
		printPoint(&sidePoint1);
		sidePoint2 = Point(receiveElements[4], receiveElements[5]);
		printPoint(&sidePoint2);

		short result = targetFinder.computeTargetPoisition(&headPoint, &sidePoint1, &sidePoint2);
		Serial.println(result);
		if (!result) {
			int realDistance = targetFinder.distanceToTarget - DISTANCE_THRESHOLD;
			if (realDistance > 0) {
				targetFinder.targetAngle -= PI_DEG;
				Serial.print("Computed angle: ");
				Serial.println(targetFinder.targetAngle);
				float angleMade = controller->turn(targetFinder.targetAngle);
				if (angleMade == 0) {
					WaitInterruptor wait(FORWARD_MS);
					controller->setInterruptor(&wait);
					controller->move();
				}
			}

		}
	}

};

void printPoint(Point* point) {
	Serial.print(point->x);
	Serial.print(" ");
	Serial.println(point->y);
}
