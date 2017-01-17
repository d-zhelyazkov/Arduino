#include <Wire.h> //I2C Arduino Library
#include<limits.h>

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

struct axis {
	int value;
	int min = INT_MAX;
	int max = INT_MIN;
	void setValue(int newValue)
	{
		value = newValue;
		if (min > value)
			min = value;
		if (max < value)
			max = value;
	}
};

char outputString[255];
axis axises[3]; //triple axis data

void setup() {
	//Initialize Serial and I2C communications
	Serial.begin(9600);
	Wire.begin();

	//Put the HMC5883 IC into the correct operating mode
	Wire.beginTransmission(address); //open communication with HMC5883
	Wire.write(0x02); //select mode register
	Wire.write(0x00); //continuous measurement mode
	Wire.endTransmission();
}


void loop() {

	int x, y, z;

	//Tell the HMC5883L where to begin reading data
	Wire.beginTransmission(address);
	Wire.write(0x03); //select register 3, X MSB register
	Wire.endTransmission();


	//Read data from each axis, 2 registers per axis
	Wire.requestFrom(address, 6);
	if (6 <= Wire.available()) {
		x = Wire.read() << 8; //X msb
		x |= Wire.read(); //X lsb
		axises[0].setValue(x);
		z = Wire.read() << 8; //Z msb
		z |= Wire.read(); //Z lsb
		axises[2].setValue(z);
		y = Wire.read() << 8; //Y msb
		y |= Wire.read(); //Y lsb
		axises[1].setValue(y);
	}
	sprintf(outputString, "x: %d, y: %d, xMin: %d, xMax: %d, yMin: %d, yMax: %d\n", x, y, axises[0].min, axises[0].max, axises[1].min, axises[1].max);
	//Print out values of each axis
	Serial.print(outputString);



	delay(250);
}
