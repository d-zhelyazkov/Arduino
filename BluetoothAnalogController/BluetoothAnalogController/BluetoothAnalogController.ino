/*
 Name:		BluetoothAnalogController.ino
 Created:	11/28/2015 5:18:47 PM
 Author:	XRC_7331
*/

#include "ExStream.h"
#include "ArduinoMotorShield.h"
#include "Main.h"


Main* main;


// the setup function runs once when you press reset or power the board
void setup() {
    main = new Main();
}

// the loop function runs over and over again until power down or reset
void loop() {
    main->loop();
}