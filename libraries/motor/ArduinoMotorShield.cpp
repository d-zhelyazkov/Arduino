#include "ArduinoMotorShield.h"


#define DEF_POWER 128

#define A_DIR 12
#define A_PWM 3
#define A_BRK 9
#define B_DIR 13
#define B_PWM 11
#define B_BRK 8


class ShieldMotor :
    public Motor
{
    byte directionPin;
    byte pwmPin;
    byte brakePin;

public:
    ShieldMotor(byte directionPin, byte pwmPin, byte brakePin) :
        directionPin(directionPin)
        , pwmPin(pwmPin)
        , brakePin(brakePin)
    {
        pinMode(directionPin, OUTPUT);
        pinMode(brakePin, OUTPUT);

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
};

Motor* const ArduinoMotorShield::MOTOR_A = new ShieldMotor(A_DIR, A_PWM, A_BRK);
Motor* const ArduinoMotorShield::MOTOR_B = new ShieldMotor(B_DIR, B_PWM, B_BRK);


