#include "ArduinoMotorShield.h"


#define DEF_POWER 128


class ShieldMotor :
    public Motor
{
    byte directionPin;
    byte pwmPin;
    byte brakePin;

    char* name;

public:
    ShieldMotor(byte directionPin, byte pwmPin, byte brakePin, char* name) :
        directionPin(directionPin)
        , pwmPin(pwmPin)
        , brakePin(brakePin)
        , name(name)
    {
        pinMode(directionPin, OUTPUT);
        pinMode(brakePin, OUTPUT);

            digitalWrite(brakePin, HIGH);
        setPower(DEF_POWER);
    }

    bool setPower(byte power) {
        analogWrite(pwmPin, power);
        return true;
    }

    bool setState(MotorState state) {
        switch (state) {
        case MotorState::STOPPED:
            digitalWrite(brakePin, HIGH);
            break;
        case MotorState::ROT_CLOCK:
            digitalWrite(directionPin, 0); //Establishes direction
            digitalWrite(brakePin, LOW);   //Disengage the Brake
            break;
        case MotorState::ROT_ANTI_CLOCK:
            digitalWrite(directionPin, 1); //Establishes direction
            digitalWrite(brakePin, LOW);   //Disengage the Brake
            break;
        }

        return true;
    }

    MotorState getState() {
        return (digitalRead(brakePin) ? MotorState::STOPPED :
            (digitalRead(directionPin) ? MotorState::ROT_ANTI_CLOCK :
                MotorState::ROT_CLOCK));
    }

    char* getName() {
        return name;
    }
};

Motor* const ArduinoMotorShield::MOTOR_A = new ShieldMotor(A_DIR, A_PWM, A_BRK, "Motor A");
Motor* const ArduinoMotorShield::MOTOR_B = new ShieldMotor(B_DIR, B_PWM, B_BRK, "Motor B");


