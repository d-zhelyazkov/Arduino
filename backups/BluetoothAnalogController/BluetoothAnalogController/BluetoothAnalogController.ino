/*
 Name:		BluetoothAnalogController.ino
 Created:	11/28/2015 5:18:47 PM
 Author:	XRC_7331
*/

#include <SoftwareSerial.h>
#include "controller\ArrowController.h"
#include "interruptor\WaitInterruptor.h"
#include "bluetooth\BluetoothModule.h"

ArrowController testController;
BluetoothModule bluetooth;

// the setup function runs once when you press reset or power the board
void setup() {
	testController.interruptor = new WaitInterruptor(300);
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (bluetooth.IsDataAvailable())
	{
		int data = bluetooth.GetNextData();
		bluetooth.SendMessage("Data received!");
		switch (data)
		{
		case 'f':
			testController.dir = MoveDir::FORWARD;
			break;
		case 'l':
			testController.dir = MoveDir::LEFT;
			break;
		case 'r':
			testController.dir = MoveDir::RIGHT;
			break;
		case 'b':
			testController.dir = MoveDir::BACKWARD;
			break;
		default:
			testController.dir = MoveDir::UNDEF;
			break;
		}

		testController.Move();
	}
}

