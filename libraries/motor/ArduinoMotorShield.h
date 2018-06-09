#pragma once
/*
Header file for Arduino Motor Shield users.
https://www.arduino.cc/en/Main/ArduinoMotorShieldR3
Corresonding pins are defined and reserved.
Motors' manipulation is being encapuslated in ShieldMotor class.
Motors on A and B ports are defined.
*/

#include "Motor.h"

#define A_DIR 12
#define A_PWM 3
#define A_BRK 9
#define B_DIR 13
#define B_PWM 11
#define B_BRK 8

class ArduinoMotorShield {
public:
    static Motor* const MOTOR_A;
    static Motor* const MOTOR_B;
};

