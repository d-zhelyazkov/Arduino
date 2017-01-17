// 
// 
// 

#include "BluetoothModule.h"

BluetoothModule::BluetoothModule()
{
	btStream = new SoftwareSerial(RX, TX);
	btStream->begin(9600);
	btStream->println("BT started!");
}

bool BluetoothModule::IsDataAvailable()
{
	return (btStream->available());
}

int BluetoothModule::GetNextData()
{
	return btStream->read();
}

void BluetoothModule::SendMessage(char* message)
{
	btStream->println(message);
}
