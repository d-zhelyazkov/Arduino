/*
 Name:		RemoteCompass.ino
 Created:	2/13/2016 3:14:13 PM
 Author:	XRC_7331
*/



// the setup function runs once when you press reset or power the board
#include <Wire.h>
#include <Adafruit_Sensor\Adafruit_Sensor.h>
#include <Adafruit_HMC5883_Unified\Adafruit_HMC5883_U.h>
#include "libs\compass\AdafruitCompass.h"

#include <SoftwareSerial.h>
#include "libs\bluetooth\BluetoothModule.h"


#define ITERATIONS 10000

Stream* btStream;
Compass* compass;
double lastDegree = 0.0;
double averageDiff = 0.0;
//char str[512];
int i = 0;

struct Max {
	double value = 0.0;
	bool trySet(double newValue)
	{
		if (newValue > value)
		{
			value = newValue;
			return true;
		}
		return false;
	}
}maxes[2];

struct Min {
	double value = 1000;
	void trySet(double newValue)
	{
		if (newValue < value)
			value = newValue;
	}
}mins[2];

void reportStatistics();

void setup() {
	btStream = getBTStream();
	compass = new AdafruitCompass();
	Serial.begin(9600);
	Serial.println("Program init");
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (i == ITERATIONS)
	{
		reportStatistics();
		i++;
		return;
	}
	else if (i > ITERATIONS)
	{
		return;
	}
	//Serial.println(str);
//delay(200);

	double degree = compass->getDegree();
	mins[0].trySet(degree);
	maxes[0].trySet(degree);
	if ((degree * lastDegree) > 0) {
		double diff = fabs(degree - lastDegree);

		averageDiff += diff / ITERATIONS;
	}
	lastDegree = degree;
	i++;
}

void reportStatistics() {
	btStream->print(" min: ");
	btStream->println(mins[0].value);
	btStream->print(" max: ");
	btStream->println(maxes[0].value);
	btStream->print(" avgDiff: ");
	btStream->println(averageDiff);

}
