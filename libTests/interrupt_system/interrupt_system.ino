#include <interrupt_system\PinInterruptCounter.h>

using namespace InterruptSystem;


PinInterruptCounter* counters[4] = { 0 };

void initCounters();
void deleteCounters();

void setup()
{
    Serial.begin(9600);
    Serial.println("\n-------------PROGRAM START-------------\n");
}

void loop()
{
    delay(1000);
    initCounters();
    for (byte i = 0; i < 10; i++) {
        Serial.println();
        for (PinInterruptCounter* counter : counters) {
            Serial.print(counter->getValue());
            Serial.print("\t");
        }
        Serial.println();
        delay(1000);
    }
    deleteCounters();
}

void initCounters() {
    Serial.println("\nCounters init.");
    counters[0] = new PinInterruptCounter(A2);
    counters[1] = new PinInterruptCounter(A3, ONRISING);
    counters[2] = new PinInterruptCounter(4, ONCHANGE);
    counters[3] = new PinInterruptCounter(12);
    for (PinInterruptCounter* counter : counters) {
        Serial.println("Attaching interrupt.");
        printInterrupt(counter);
        attachInterrupt(counter);
    }
    Serial.println("\nCounters init finished.\n");
}

void deleteCounters() {
    Serial.println("\nDeleting counters.");
    for (PinInterruptCounter* counter : counters) {
        Serial.println("\nDeleting counter.");
        printInterrupt(counter);
        //deattachInterrupt(counter);
        delete counter;
    }
    Serial.println("\nDeleting counters finished.");
}
