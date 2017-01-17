/*
 Name:		BluetoothAnalogController.ino
 Created:	11/28/2015 5:18:47 PM
 Author:	XRC_7331
*/

#include <SoftwareSerial.h>
#include "controller\ArrowController.h"
#include "interruptor\WaitInterruptor.h"
#include "bluetooth\BluetoothModule.h"

#define REQUEST_DIRECTION "0"
#define RESEND_CYCLE 10
#define CYCLE_DELAY 200

ArrowController testController;
BluetoothModule bluetooth;
unsigned short timeSinceWastRequest = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	//testController.interruptor = new WaitInterruptor(300);

	bluetooth.SendMessage(REQUEST_DIRECTION);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (!(timeSinceWastRequest % RESEND_CYCLE))
	{
		bluetooth.SendMessage(REQUEST_DIRECTION);
		timeSinceWastRequest = 0;
	}
	if (bluetooth.IsDataAvailable())
	{
		char data = bluetooth.GetNextData();

		if ((data < 0) || (data >= MOVE_DIR_CNT))
			data = 0;
		testController.dir = static_cast<MoveDir>(data);

		testController.Move();

		bluetooth.SendMessage(REQUEST_DIRECTION);
		timeSinceWastRequest = 0;
	}
	delay(CYCLE_DELAY);
	testController.Stop();
	timeSinceWastRequest = timeSinceWastRequest + 1;
}

