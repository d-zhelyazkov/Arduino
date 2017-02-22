#pragma once

#include "ExStream.h"
#include "ArduinoMotorShield.h"
#include "SoftwareSerial.h"
#include "AnalogJoystickController.h"

#define REQUEST_ANALOG_INFO "1"
#define RESEND_CYCLE 10
#define CYCLE_DELAY 200

#define RX 1
#define TX 2


class Main {
    AnalogJoystickController* analogJoystickController;
    ExStream* btStream = 0;

public:
    Main() {
        analogJoystickController = new AnalogJoystickController(ArduinoMotorShield::MOTOR_A, ArduinoMotorShield::MOTOR_B);
        SoftwareSerial* serial = new SoftwareSerial(RX, TX);
        serial->begin(9600);
        btStream = new ExStream(serial);
    }

    void loop() {
        Stream* btBaseStream = btStream->getBaseStream();
        for (byte i = 0; !btBaseStream->available() && i < RESEND_CYCLE; i++)
            delay(CYCLE_DELAY);

        if (!btStream->getBaseStream()->available()) {
            btBaseStream->println(REQUEST_ANALOG_INFO);
            return;
        }

        float x, y;
        btStream->read(&x);
        btStream->read(&y);

        analogJoystickController->move(x, y);

        btBaseStream->println(REQUEST_ANALOG_INFO);

        delay(CYCLE_DELAY);
        analogJoystickController->stop();
    }
};