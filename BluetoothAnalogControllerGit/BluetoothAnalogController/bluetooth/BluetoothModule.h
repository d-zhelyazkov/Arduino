// BluetoothModule.h

#ifndef _BLUETOOTHMODULE_h
#define _BLUETOOTHMODULE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include <SoftwareSerial.h>

#define RX 1
#define TX 2
#define FLOAT_SIZE 4

class BluetoothModule
{
	SoftwareSerial* btStream;

public:
	BluetoothModule();
	bool IsDataAvailable();
	byte GetNextData();
	float GetFloat();
	void SendMessage(char* message);
};

#endif

