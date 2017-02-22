#pragma once
/*
Header file for Arduino Motor Shield users.
https://www.arduino.cc/en/Main/ArduinoMotorShieldR3
Corresonding pins are defined and reserved.
Motors' manipulation is being encapuslated in ShieldMotor class.
Motors on A and B ports are defined.
*/

#include "Motor.h"

class ArduinoMotorShield {
public:
    static Motor* const MOTOR_A;
    static Motor* const MOTOR_B;
};

