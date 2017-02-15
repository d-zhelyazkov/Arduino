#include "ArduinoMotorShield.h"


#define DEF_POWER 128

#define A_DIR 12
#define A_PWM 3
#define A_BRK 9
#define B_DIR 13
#define B_PWM 11
#define B_BRK 8

namespace ArduinoMotorShield {

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

        void setPower(byte power) {
            analogWrite(pwmPin, power);
        }

        bool setState(MotorState state) {
            Motor::setState(state);

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
    };

    Motor* MOTOR_A = new ShieldMotor(A_DIR, A_PWM, A_BRK);
    Motor* MOTOR_B = new ShieldMotor(B_DIR, B_PWM, B_BRK);

};

