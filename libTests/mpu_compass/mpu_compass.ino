/*
Name:		MPUCompassTest.ino
Created:	7/10/2016 7:23:40 PM
Author:	XRC_7331
*/
#include <MPUCompass.h>

// the setup function runs once when you press reset or power the board
MPUCompass* compass;
void setup() {
    Serial.begin(9600);
    Serial.println("Program started.");
    compass = new MPUCompass();
    //compass->startListening();
}

// the loop function runs over and over again until power down or reset
void loop() {
    delay(1000);
    Serial.print("Compass: ");
    Serial.println(compass->getDirectionInDegrees());
}
