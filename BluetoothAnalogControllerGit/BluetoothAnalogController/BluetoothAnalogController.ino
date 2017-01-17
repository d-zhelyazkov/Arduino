/*
 Name:		BluetoothAnalogController.ino
 Created:	11/28/2015 5:18:47 PM
 Author:	XRC_7331
*/

#include <SoftwareSerial.h>
#include "controller\AnalogJoystickController.h"
#include "interruptor\WaitInterruptor.h"
#include "bluetooth\BluetoothModule.h"

#define REQUEST_DIRECTION "0"
#define REQUEST_ANALOG_INFO "1"
#define RESEND_CYCLE 10
#define CYCLE_DELAY 200

AnalogJoystickController analogJoystickController;
BluetoothModule bluetooth;
unsigned short timeSinceWastRequest = 0;

// the setup function runs once when you press reset or power the board
void setup() {
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (!(timeSinceWastRequest % RESEND_CYCLE))
	{
		bluetooth.SendMessage(REQUEST_ANALOG_INFO);
		timeSinceWastRequest = 0;
	}
	if (bluetooth.IsDataAvailable())
	{
		analogJoystickController.x = bluetooth.GetFloat();
		analogJoystickController.y = bluetooth.GetFloat();

		analogJoystickController.Move();

		bluetooth.SendMessage(REQUEST_ANALOG_INFO);
		timeSinceWastRequest = 0;
	}
	delay(CYCLE_DELAY);
	analogJoystickController.Stop();
	timeSinceWastRequest = timeSinceWastRequest + 1;
}

