#include "Wire.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPUCompass.h"

#include "SoftwareSerial.h"
#include "ExStream.h"

#include "controller\AngularController3.h"

#include "Main.h"

Main mainProgram;

void setup()
{
	Serial.begin(9600);
	mainProgram.init();
	Serial.println("Program start");
}

void loop()
{
	mainProgram.loopBody();
}



