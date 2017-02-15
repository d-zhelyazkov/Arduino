/*
 Name:		BluetoothAnalogController.ino
 Created:	11/28/2015 5:18:47 PM
 Author:	XRC_7331
*/

#include "SoftwareSerial.h"
#include "AnalogJoystickController.h"
#include "ExStream.h"
#include "ArduinoMotorShield.h"

#define REQUEST_DIRECTION "0"
#define REQUEST_ANALOG_INFO "1"
#define RESEND_CYCLE 10
#define CYCLE_DELAY 200

#define RX 1
#define TX 2

AnalogJoystickController analogJoystickController(ArduinoMotorShield::MOTOR_A, ArduinoMotorShield::MOTOR_B);
ExStream* btStream = 0;

// the setup function runs once when you press reset or power the board
void setup() {
    SoftwareSerial* serial = new SoftwareSerial(RX, TX);
    serial->begin(9600);
    btStream = new ExStream(serial);
}

// the loop function runs over and over again until power down or reset
void loop() {
    for (byte i = 0; !btStream->getBaseStream()->available() && i < RESEND_CYCLE; i++)
        delay(CYCLE_DELAY);

    if (!btStream->getBaseStream()->available()) {
        btStream->println(REQUEST_ANALOG_INFO);
        return;
    }
    
    float x, y;
    btStream->readObject(&x);
    btStream->readObject(&y);

    analogJoystickController.move(x, y);

    btStream->getBaseStream()->println(REQUEST_ANALOG_INFO);
    
    delay(CYCLE_DELAY);
    analogJoystickController.stop();
}

