#include <eeprom_ex.h>

#define VARS 10

void setup()
{

	Serial.begin(9600);
	Serial.println("\n\n---------------PROGRAM START---------------");
	Serial.println("\nReading values.");
	uint16_t values[VARS];
	for (byte i = 0; i < VARS; i++) {
		eeprom_get<uint16_t>(i, values[i]);
		Serial.print(values[i]);
		Serial.print(" ");
	}

	Serial.println("\nWriting values.");
	for (byte i = 0; i < VARS; i++) {
		uint16_t value = values[i] + i;
		Serial.print(value);
		Serial.print(" ");
		eeprom_set(i, value);
	}
	Serial.println("\nWriting completed.");
}

void loop()
{

  /* add main program code here */

}
