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
        directionPin(directionPin), pwmPin(pwmPin), brakePin(brakePin), name(name)
    {

        pinMode(directionPin, OUTPUT);
        pinMode(brakePin, OUTPUT);

        stop();
        setPower(DEF_POWER);
    }

    bool setPower(byte power) {
        analogWrite(pwmPin, power);
        return true;
    }

    bool setState(MotorState state) {

        switch (state) {
        case MotorState::STOPPED:
            return stop();
        case MotorState::ROT_CLOCK:
        case MotorState::ROT_ANTI_CLOCK:
            return (
                setDirection(state) 
                && start());
        }

        return false;
    }

    bool setDirection(MotorState state) {

        switch (state)
        {
        case ROT_CLOCK:
            digitalWrite(directionPin, LOW); //Establishes direction
            return true;
        case ROT_ANTI_CLOCK:
            digitalWrite(directionPin, HIGH);
            return true;
        }

        return false;
    }

    bool start() {
        digitalWrite(brakePin, LOW);   //Disengage the Brake
        return true;
    }

    bool stop() {
        digitalWrite(brakePin, HIGH);
        return true;
    }

    MotorState getState() {
        return (digitalRead(brakePin)
            ? MotorState::STOPPED
            : (digitalRead(directionPin)
                ? MotorState::ROT_ANTI_CLOCK
                : MotorState::ROT_CLOCK));
    }

    char* getName() {
        return name;
    }
};

Motor* const ArduinoMotorShield::MOTOR_A = new ShieldMotor(A_DIR, A_PWM, A_BRK, "Motor A");
Motor* const ArduinoMotorShield::MOTOR_B = new ShieldMotor(B_DIR, B_PWM, B_BRK, "Motor B");


