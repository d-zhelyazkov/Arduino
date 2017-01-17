#include <MotorWithEncoder.h>

#define A_DIR 12
#define A_PWM 3
#define A_BRK 9
#define B_DIR 13
#define B_PWM 11
#define B_BRK 8

#define A_ENC A2
#define B_ENC A3

#define MAX_POWER 255
#define MIN_POWER 100

MotorWithEncoder motorA(A_DIR, A_PWM, A_BRK, A_ENC);
MotorWithEncoder motorB(B_DIR, B_PWM, B_BRK, B_ENC);

void setup()
{

  /* add setup code here */
	Serial.begin(9600);
	Serial.println("-----------------------PROGRAM SETUP----------------");

	Serial.println("Starting motor A");
	motorA.setPower(MIN_POWER);
	motorA.move(State::ROT_CLOCK, 50);
	Serial.println("Starting motor B");
	motorB.setPower(MIN_POWER);
	motorB.move(State::ROT_ANTI_CLOCK, 20);

}

void loop()
{

  /* add main program code here */

}
