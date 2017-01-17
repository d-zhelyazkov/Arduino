// 
// 
// 

#include "BluetoothModule.h"

BluetoothModule::BluetoothModule()
{
	btStream = new SoftwareSerial(RX, TX);
	btStream->begin(9600);
	btStream->println("BT started!");
	//btStream->flush();
}

bool BluetoothModule::IsDataAvailable()
{
	return (btStream->available());
}

byte BluetoothModule::GetNextData()
{
	return btStream->read();
}

void BluetoothModule::SendMessage(char* message)
{
	btStream->println(message);
}

float BluetoothModule::GetFloat()
{
	float result;
	byte receivedBytes[FLOAT_SIZE];
	for (int i = FLOAT_SIZE - 1; i >= 0; i--)
	{
		while (!IsDataAvailable());
		receivedBytes[i] = GetNextData();
	}

	memcpy(&result, &receivedBytes, sizeof(result));
	return result;

}
