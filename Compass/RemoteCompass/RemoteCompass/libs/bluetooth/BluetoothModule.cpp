
#include "BluetoothModule.h"


#include <SoftwareSerial\SoftwareSerial.h>

#define RX 2
#define TX 4

Stream* getBTStream() {
	SoftwareSerial* btStream = new SoftwareSerial(RX, TX);
	btStream->begin(9600);
	btStream->println("BT started!");
	//btStream->flush();
	return btStream;
}


