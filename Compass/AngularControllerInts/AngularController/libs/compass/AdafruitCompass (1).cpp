

#include "AdafruitCompass.h"

#define PI_DEG 180
#define STATISTICS 10
const int PI_DEGx2 = (PI_DEG << 1);

void AdafruitCompass::displaySensorDetails(void)
{
	sensor_t sensor;
	mag->getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.print("Sensor:       "); Serial.println(sensor.name);
	Serial.print("Driver Ver:   "); Serial.println(sensor.version);
	Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
	Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
	Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
	Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
	Serial.println("------------------------------------");
	Serial.println("");
	//delay(500);
}

AdafruitCompass::AdafruitCompass()
{
	/* Assign a unique ID to this sensor at the same time */
	mag = new Adafruit_HMC5883_Unified(12345);

	/* Initialise the sensor */
	if (!mag->begin())
	{
		/* There was a problem detecting the HMC5883 ... check your connections */
		Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
		while (1);
	}

	/* Display some basic information on this sensor */
	//displaySensorDetails();
}

//[-PI;PI], averaged
float AdafruitCompass::getDirectionInRadians()
{
	/* Get a new sensor event */
	float sum = 0.0;
	for (int i = 0; i < STATISTICS; i++)
	{
		sensors_event_t event;
		mag->getEvent(&event);
		sum += atan2(event.magnetic.y, event.magnetic.x);
	}
	float heading = sum / STATISTICS;
	/* Display the results (magnetic vector values are in micro-Tesla (uT)) */
	/*Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
	Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
	Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  "); Serial.println("uT");*/

	// Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
	// Calculate heading when the magnetometer is level, then correct for signs of axis.
	//float heading = atan2(event.magnetic.y, event.magnetic.x);

	//// Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
	//// Find yours here: http://www.magnetic-declination.com/
	//// Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
	//// If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
	///*float declinationAngle = 0.22;
	//heading += declinationAngle;*/

	//// Correct for when signs are reversed.
	//if (heading < 0)
	//	heading += 2 * PI;

	//// Check for wrap due to addition of declination.
	//if (heading > 2 * PI)
	//	heading -= 2 * PI;

	//// Convert radians to degrees for readability.
	//heading = heading * 180 / M_PI;

	////Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

	return heading;
}

//[0;2PI]
float AdafruitCompass::getDirectionInDegrees() {
	float radians = this->getDirectionInRadians();
	float degrees = radians * PI_DEG / PI;
	degrees = fmod(degrees, PI_DEGx2);
	if (degrees < 0)
		degrees += (PI_DEGx2);

	return degrees;
}
