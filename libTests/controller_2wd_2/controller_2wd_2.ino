#include "ArduinoMotorShield.h"
#include <MotorWithEncoder.h>
#include <MPUCompass.h>

#include "Controller2WDv2.h"

#define A_ENC A2
#define B_ENC A3


MotorWithEncoder motorA(ArduinoMotorShield::MOTOR_A, A_ENC);
MotorWithEncoder motorB(ArduinoMotorShield::MOTOR_B, B_ENC);

MPUCompass* compass;
Controller2WDv2* controller;


void setup()
{
    Serial.begin(9600);
    Serial.println("------------------PROGRAM START-------------");
    
    compass = new MPUCompass();
    controller = new Controller2WDv2(&motorA, &motorB, compass);
    //controller->learn();

    Serial.println("Awaiting command");
}

void loop()
{
    delay(1000);
    if (!Serial.available())
        return;

    String command = Serial.readString();
    if (command.equalsIgnoreCase("learn")) {
        //compass->startListening();
        controller->learn();
        //compass->stopListening();
    }
    else if (command.equalsIgnoreCase("turn")) {
        Serial.println("Give a degree.");
        while (!Serial.available())
            delay(1000);

        short degree = Serial.parseInt();
        controller->turn(degree);
    }
    else if (command.equalsIgnoreCase("move")) {
        Serial.println("How many ticks?");
        while (!Serial.available())
            delay(1000);

        short ticks = Serial.parseInt();
        controller->move(ticks);
    }
    else {
        Serial.println("Command not matched correctly! Commands: [Learn,Turn, Move]\n");
    }

    Serial.println("Awaiting command");
}
