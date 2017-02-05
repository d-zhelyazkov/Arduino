#include <MotorWithEncoder.h>
#include <MPUCompass.h>

#include "Controller2WDv2.h"


//arduino motor shield pins
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

#define MPU_INT_PIN 2


MotorWithEncoder motorA(A_DIR, A_PWM, A_BRK, A_ENC);
MotorWithEncoder motorB(B_DIR, B_PWM, B_BRK, B_ENC);

MPUCompass* compass;
Controller2WDv2* controller;


void setup()
{
    Serial.begin(9600);
    Serial.println("------------------PROGRAM START-------------");

    motorA.setPower(MIN_POWER);
    motorB.setPower(MIN_POWER);

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
