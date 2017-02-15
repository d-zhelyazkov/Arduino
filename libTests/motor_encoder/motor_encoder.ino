#include "ArduinoMotorShield.h"
#include "MotorWithEncoder.h"


#define A_ENC A2
#define B_ENC A3



MotorWithEncoder motorA(ArduinoMotorShield::MOTOR_A, A_ENC);
MotorWithEncoder motorB(ArduinoMotorShield::MOTOR_B, B_ENC);

void setup()
{

  /* add setup code here */
	Serial.begin(9600);
	Serial.println("-----------------------PROGRAM SETUP----------------");

	Serial.println("Starting motor A");
	motorA.move(MotorState::ROT_CLOCK, 50);
	Serial.println("Starting motor B");
	motorB.move(MotorState::ROT_ANTI_CLOCK, 20);

}

void loop()
{

  /* add main program code here */

}
