// AdafruitCompass.h
/***************************************************************************
This is a library example for the HMC5883 magnentometer/compass

Designed specifically to work with the Adafruit HMC5883 Breakout
http://www.adafruit.com/products/1746

*** You will also need to install the Adafruit_Sensor library! ***

These displays use I2C to communicate, 2 pins are required to interface.

Adafruit invests time and resources providing this open source code,
please support Adafruit andopen-source hardware by purchasing products
from Adafruit!

Written by Kevin Townsend for Adafruit Industries with some heading example from
Love Electronics (loveelectronics.co.uk)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

***************************************************************************/
#ifndef _ADAFRUITCOMPASS_h
#define _ADAFRUITCOMPASS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <Adafruit_Sensor\Adafruit_Sensor.h>
#include <Adafruit_HMC5883_Unified\Adafruit_HMC5883_U.h>
#include "compass.h"

//pins: SDA - 4, SCL - 5

class AdafruitCompass : public Compass {
private:
	Adafruit_HMC5883_Unified* mag;

	void displaySensorDetails(void);

public:
	AdafruitCompass();

	float getDirectionInRadians();
	float getDirectionInDegrees();
};

#endif

