#include <Interrupt.h>

class IntCounter : public Interrupt {
public:
    volatile unsigned counter = 0;
    IntCounter(byte pin) : Interrupt(pin) {}
    IntCounter(byte pin, InterruptMode mode) : Interrupt(pin, mode) {}
    void interruptServiceRoutine() { counter++; }
};

IntCounter* counters[4] = { 0 };

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
        for (IntCounter* counter : counters) {
            Serial.print(counter->counter);
            Serial.print("\t");
        }
        Serial.println();
        delay(1000);
    }
    deleteCounters();
}

void initCounters() {
    Serial.println("\nCounters init.");
    counters[0] = new IntCounter(A2);
    counters[1] = new IntCounter(A3, ONRISING);
    counters[2] = new IntCounter(4, ONCHANGE);
    counters[3] = new IntCounter(12);
    for (IntCounter* counter : counters) {
        Serial.println("Attaching interrupt.");
        printInterrupt(counter);
        attachInterrupt(counter);
    }
    Serial.println("\nCounters init finished.\n");
}

void deleteCounters() {
    Serial.println("\nDeleting counters.");
    for (IntCounter* counter : counters) {
        Serial.println("\nDeleting counter.");
        printInterrupt(counter);
        //deattachInterrupt(counter);
        delete counter;
    }
    Serial.println("\nDeleting counters finished.");
}
